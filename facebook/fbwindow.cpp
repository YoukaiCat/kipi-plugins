/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.digikam.org
 *
 * Date        : 2005-17-26
 * Description : a kipi plugin to import/export images to Facebook web service
 *
 * Copyright (C) 2005-2008 by Vardhman Jain <vardhman at gmail dot com>
 * Copyright (C) 2008-2015 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2008-2009 by Luka Renko <lure at kubuntu dot org>
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

#include "fbwindow.h"

// Qt includes

#include <QComboBox>
#include <QMenu>
#include <QFileInfo>
#include <QCheckBox>
#include <QCloseEvent>
#include <QSpinBox>

// KDE includes

#include <kconfig.h>
#include <klocalizedstring.h>
#include <kmessagebox.h>
#include <KWindowConfig>

// LibKDcraw includes

#include <libkdcraw_version.h>
#include <KDCRAW/KDcraw>

// Libkipi includes

#include <KIPI/Interface>

// Local includes

#include "kipiplugins_debug.h"
#include "kpimageslist.h"
#include "kpaboutdata.h"
#include "kpimageinfo.h"
#include "kpmetadata.h"
#include "kpversion.h"
#include "kpprogresswidget.h"
#include "fbitem.h"
#include "fbtalker.h"
#include "fbwidget.h"
#include "fbalbum.h"

namespace KIPIFacebookPlugin
{

FbWindow::FbWindow(const QString& tmpFolder, QWidget* const /*parent*/)
    : KPToolDialog(0)
{
    m_tmpPath.clear();
    m_tmpDir      = tmpFolder;
    m_imagesCount = 0;
    m_imagesTotal = 0;
    m_widget      = new FbWidget(this);

    setMainWidget(m_widget);
    setWindowIcon(QIcon::fromTheme(QStringLiteral("kipi-facebook")));
    setModal(false);

    setWindowTitle(i18n("Export to Facebook Web Service"));

    startButton()->setText(i18n("Start Upload"));
    startButton()->setToolTip(i18n("Start upload to Facebook web service"));

    m_widget->setMinimumSize(700, 500);
    // ------------------------------------------------------------------------

    connect(m_widget->m_imgList, SIGNAL(signalImageListChanged()),
            this, SLOT(slotImageListChanged()));

    connect(m_widget->m_changeUserBtn, SIGNAL(clicked()),
            this, SLOT(slotUserChangeRequest()));

    connect(m_widget->m_newAlbumBtn, SIGNAL(clicked()),
            this, SLOT(slotNewAlbumRequest()));

    connect(m_widget, SIGNAL(reloadAlbums(long long)),
            this, SLOT(slotReloadAlbumsRequest(long long)));

    connect(startButton(), SIGNAL(clicked()),
            this, SLOT(slotStartTransfer()));

    connect(this, SIGNAL(finished(int)),
            this, SLOT(slotFinished()));

    connect(this, SIGNAL(cancelClicked()),
            this, SLOT(slotCancelClicked()));

    // ------------------------------------------------------------------------

    KPAboutData* about = new KPAboutData(ki18n("Facebook Export"), 0,
                                         KAboutLicense::GPL,
                                         ki18n("A Kipi plugin to export image collection "
                                               "to/from Facebook web service."),
                                         ki18n("(c) 2005-2008, Vardhman Jain\n"
                                               "(c) 2008-2012, Gilles Caulier\n"
                                               "(c) 2008-2009, Luka Renko"));

    about->addAuthor(ki18n("Luka Renko").toString(),
                     ki18n("Author and maintainer").toString(),
                     QStringLiteral("lure at kubuntu dot org"));

    about->setHandbookEntry(QStringLiteral("facebook"));
    setAboutData(about);

    // ------------------------------------------------------------------------

    m_albumDlg = new FbNewAlbum(this);

    // ------------------------------------------------------------------------

    m_talker = new FbTalker(this);

    connect(m_talker, SIGNAL(signalBusy(bool)),
            this, SLOT(slotBusy(bool)));

    connect(m_talker, SIGNAL(signalLoginProgress(int,int,QString)),
            this, SLOT(slotLoginProgress(int,int,QString)));

    connect(m_talker, SIGNAL(signalLoginDone(int,QString)),
            this, SLOT(slotLoginDone(int,QString)));

    connect(m_talker, SIGNAL(signalAddPhotoDone(int,QString)),
            this, SLOT(slotAddPhotoDone(int,QString)));

    connect(m_talker, SIGNAL(signalCreateAlbumDone(int,QString,QString)),
            this, SLOT(slotCreateAlbumDone(int,QString,QString)));

    connect(m_talker, SIGNAL(signalListAlbumsDone(int,QString,QList<FbAlbum>)),
            this, SLOT(slotListAlbumsDone(int,QString,QList<FbAlbum>)));

    connect(m_widget->progressBar(), SIGNAL(signalProgressCanceled()),
            this, SLOT(slotStopAndCloseProgressBar()));

    // ------------------------------------------------------------------------

    readSettings();

    qCDebug(KIPIPLUGINS_LOG) << "Calling Login method";
    buttonStateChange(m_talker->loggedIn());
    authenticate();
}

FbWindow::~FbWindow()
{
}

void FbWindow::slotStopAndCloseProgressBar()
{
    // Cancel the operation
    slotCancelClicked();

    // Write settings and tidy up
    slotFinished();

    // Close the dialog
    reject();
}

void FbWindow::slotFinished()
{
    writeSettings();
    m_widget->imagesList()->listView()->clear();
    m_widget->progressBar()->progressCompleted();
}

void FbWindow::slotCancelClicked()
{
    setRejectButtonMode(QDialogButtonBox::Close);
    m_talker->cancel();
    m_transferQueue.clear();
    m_widget->m_imgList->cancelProcess();
    m_widget->progressBar()->hide();
    m_widget->progressBar()->progressCompleted();
}

void FbWindow::reactivate()
{
    m_widget->imagesList()->loadImagesFromCurrentSelection();
    show();
}

void FbWindow::closeEvent(QCloseEvent* e)
{
    if (!e)
    {
        return;
    }

    slotFinished();
    e->accept();
}

void FbWindow::readSettings()
{
    KConfig config(QStringLiteral("kipirc"));
    KConfigGroup grp = config.group("Facebook Settings");
    m_accessToken    = grp.readEntry("Access Token");
    m_sessionExpires = grp.readEntry("Session Expires", 0);

    if (m_accessToken.isEmpty())
    {
        m_sessionKey     = grp.readEntry("Session Key");
        m_sessionSecret  = grp.readEntry("Session Secret");
    }

    m_currentAlbumID = grp.readEntry("Current Album", QString());

    if (grp.readEntry("Resize", false))
    {
        m_widget->m_resizeChB->setChecked(true);
        m_widget->m_dimensionSpB->setEnabled(true);
        m_widget->m_imageQualitySpB->setEnabled(true);
    }
    else
    {
        m_widget->m_resizeChB->setChecked(false);
        m_widget->m_dimensionSpB->setEnabled(false);
        m_widget->m_imageQualitySpB->setEnabled(false);
    }

    m_widget->m_dimensionSpB->setValue(grp.readEntry("Maximum Width", 604));
    m_widget->m_imageQualitySpB->setValue(grp.readEntry("Image Quality", 85));

    KConfigGroup dialogGroup = config.group("Facebook Export Dialog");
    KWindowConfig::restoreWindowSize(windowHandle(), dialogGroup);
}

void FbWindow::writeSettings()
{
    KConfig config(QStringLiteral("kipirc"));
    KConfigGroup grp = config.group("Facebook Settings");
    grp.writeEntry("Access Token",    m_accessToken);

    /* If we have both access token and session key, then we have just converted one into the other. */
    if (! m_accessToken.isEmpty())
    {
        if (! m_sessionKey.isEmpty())
        {
            grp.deleteEntry("Session Key");
        }

        if (! m_sessionSecret.isEmpty())
        {
            grp.deleteEntry("Session Secret");
        }
    }
    
    grp.writeEntry("Session Expires", m_sessionExpires);
    grp.writeEntry("Current Album",   m_currentAlbumID);
    grp.writeEntry("Resize",          m_widget->m_resizeChB->isChecked());
    grp.writeEntry("Maximum Width",   m_widget->m_dimensionSpB->value());
    grp.writeEntry("Image Quality",   m_widget->m_imageQualitySpB->value());

    KConfigGroup dialogGroup = config.group("Facebook Export Dialog");
    KWindowConfig::saveWindowSize(windowHandle(), dialogGroup);

    config.sync();
}

void FbWindow::authenticate()
{
    setRejectButtonMode(QDialogButtonBox::Cancel);
    m_widget->progressBar()->show();
    m_widget->progressBar()->setFormat(QStringLiteral(""));

    // Converting old world session keys into OAuth2 tokens
    if (! m_sessionKey.isEmpty() && m_accessToken.isEmpty())
    {
        qCDebug(KIPIPLUGINS_LOG) << "Exchanging session tokens to OAuth";
        m_talker->exchangeSession(m_sessionKey);
    }
    else
    {
        qCDebug(KIPIPLUGINS_LOG) << "Calling Login method";
        m_talker->authenticate(m_accessToken, m_sessionExpires);
    }
}

void FbWindow::slotLoginProgress(int step, int maxStep, const QString& label)
{
    KIPIPlugins::KPProgressWidget* progressBar = m_widget->progressBar();

    if (!label.isEmpty())
    {
        progressBar->setFormat(label);
    }

    if (maxStep > 0)
    {
        progressBar->setMaximum(maxStep);
    }

    progressBar->setValue(step);
}

void FbWindow::slotLoginDone(int errCode, const QString& errMsg)
{
    setRejectButtonMode(QDialogButtonBox::Close);
    m_widget->progressBar()->hide();

    buttonStateChange(m_talker->loggedIn());
    FbUser user = m_talker->getUser();
    setProfileAID(user.id);
    m_widget->updateLabels(user.name, user.profileURL, user.uploadPerm);
    m_widget->m_albumsCoB->clear();

    m_widget->m_albumsCoB->addItem(i18n("<auto create>"), QString());

    m_accessToken    = m_talker->getAccessToken();
    m_sessionExpires = m_talker->getSessionExpires();

    if (errCode == 0 && m_talker->loggedIn())
    {
        m_talker->listAlbums();    // get albums to fill combo box
    }
    else
    {
        KMessageBox::error(this, i18n("Facebook Call Failed: %1\n", errMsg));
    }
}

void FbWindow::slotListAlbumsDone(int errCode, const QString& errMsg, const QList<FbAlbum>& albumsList)
{

    QString albumDebug = QStringLiteral("");
    foreach(const FbAlbum &album, albumsList)
    {
        albumDebug.append(QStringLiteral("%1: %2\n").arg(album.id).arg(album.title));
    }

    qCDebug(KIPIPLUGINS_LOG) << "Received albums (errCode = " << errCode << ", errMsg = "
             << errMsg << "): " << albumDebug;

    if (errCode != 0)
    {
        KMessageBox::error(this, i18n("Facebook Call Failed: %1\n", errMsg));
        return;
    }

    m_widget->m_albumsCoB->clear();
    m_widget->m_albumsCoB->addItem(i18n("<auto create>"), QString());

    for (int i = 0; i < albumsList.size(); ++i)
    {
        QString albumIcon;

        switch (albumsList.at(i).privacy)
        {
            case FB_ME:
                albumIcon = QStringLiteral("secure-card");
                break;

            case FB_FRIENDS:
                albumIcon = QStringLiteral("user-identity");
                break;

            case FB_FRIENDS_OF_FRIENDS:
                albumIcon = QStringLiteral("system-users");
                break;

            case FB_NETWORKS:
                albumIcon = QStringLiteral("network-workgroup");
                break;

            case FB_EVERYONE:
                albumIcon = QStringLiteral("applications-internet");
                break;

            case FB_CUSTOM:
                albumIcon = QStringLiteral("configure");
                break;
        }

        m_widget->m_albumsCoB->addItem(
            QIcon::fromTheme(albumIcon),
            albumsList.at(i).title,
            albumsList.at(i).id);

        if (m_currentAlbumID == albumsList.at(i).id)
        {
            m_widget->m_albumsCoB->setCurrentIndex(i + 1);
        }
    }
}

void FbWindow::buttonStateChange(bool state)
{
    m_widget->m_newAlbumBtn->setEnabled(state);
    m_widget->m_reloadAlbumsBtn->setEnabled(state);
    startButton()->setEnabled(state);
}

void FbWindow::slotBusy(bool val)
{
    if (val)
    {
        setCursor(Qt::WaitCursor);
        m_widget->m_changeUserBtn->setEnabled(false);
        buttonStateChange(false);
    }
    else
    {
        setCursor(Qt::ArrowCursor);
        m_widget->m_changeUserBtn->setEnabled(true);
        buttonStateChange(m_talker->loggedIn());
    }
}

void FbWindow::slotUserChangeRequest()
{
    qCDebug(KIPIPLUGINS_LOG) << "Slot Change User Request";

    if (m_talker->loggedIn())
    {
        m_talker->logout();
        QMessageBox warn(QMessageBox::Warning,
                     i18n("Warning"),
                     i18n("After you have been logged out in the browser, "
                          "click \"Continue\" to authenticate for another account"),
                     QMessageBox::Yes | QMessageBox::No);
    
        (warn.button(QMessageBox::Yes))->setText(i18n("Continue"));
        (warn.button(QMessageBox::No))->setText(i18n("Cancel"));      
    
        if (warn.exec() == QMessageBox::Yes)
        {
            m_accessToken.clear();
            m_sessionExpires = 0;
        }
        else
            return;
    }

    authenticate();
}

void FbWindow::slotReloadAlbumsRequest(long long userID)
{
    qCDebug(KIPIPLUGINS_LOG) << "Reload Albums Request for UID:" << userID;

    if (userID == 0)
    {
        FbUser user = m_talker->getUser();
        setProfileAID(user.id);
        m_talker->listAlbums(); // re-get albums from current user
    }
    else
    {
        setProfileAID(userID);
        m_talker->listAlbums(userID); // re-get albums for friend
    }
}

void FbWindow::slotNewAlbumRequest()
{
    qCDebug(KIPIPLUGINS_LOG) << "Slot New Album Request";

    if (m_albumDlg->exec() == QDialog::Accepted)
    {
        qCDebug(KIPIPLUGINS_LOG) << "Calling New Album method";
        FbAlbum newAlbum;
        m_albumDlg->getAlbumProperties(newAlbum);
        m_talker->createAlbum(newAlbum);
    }
}

void FbWindow::slotStartTransfer()
{
    qCDebug(KIPIPLUGINS_LOG) << "slotStartTransfer invoked";

    m_widget->m_imgList->clearProcessedStatus();
    m_transferQueue  = m_widget->m_imgList->imageUrls();

    if (m_transferQueue.isEmpty())
    {
        return;
    }

    m_currentAlbumID = m_widget->m_albumsCoB->itemData(m_widget->m_albumsCoB->currentIndex()).toString();
    qCDebug(KIPIPLUGINS_LOG) << "upload request got album id from widget: " << m_currentAlbumID;
    m_imagesTotal    = m_transferQueue.count();
    m_imagesCount    = 0;

    setRejectButtonMode(QDialogButtonBox::Cancel);
    m_widget->progressBar()->setFormat(i18n("%v / %m"));
    m_widget->progressBar()->setMaximum(m_imagesTotal);
    m_widget->progressBar()->setValue(0);
    m_widget->progressBar()->show();
    m_widget->progressBar()->progressScheduled(i18n("Facebook export"), true, true);
    m_widget->progressBar()->progressThumbnailChanged(QIcon::fromTheme(QStringLiteral("kipi")).pixmap(22, 22));

    uploadNextPhoto();
}

void FbWindow::setProfileAID(long long userID)
{
    // store AID of Profile Photos album
    // http://wiki.developers.facebook.com/index.php/Profile_archive_album
    m_profileAID = QString::number((userID << 32)
                                   + (-3 & 0xFFFFFFFF));
}

QString FbWindow::getImageCaption(const QString& fileName)
{
    KPImageInfo info(QUrl::fromLocalFile(fileName));
    // Facebook doesn't support image titles. Include it in descriptions if needed.
    QStringList descriptions = QStringList() << info.title() << info.description();
    descriptions.removeAll(QStringLiteral(""));
    return descriptions.join(QStringLiteral("\n\n"));
}

bool FbWindow::prepareImageForUpload(const QString& imgPath, bool isRAW, QString& caption)
{
    QImage image;

    if (isRAW)
    {
        qCDebug(KIPIPLUGINS_LOG) << "Get RAW preview " << imgPath;
        KDcrawIface::KDcraw::loadRawPreview(image, imgPath);
    }
    else
    {
        image.load(imgPath);
    }

    if (image.isNull())
    {
        return false;
    }

    // get temporary file name
    m_tmpPath = m_tmpDir + QFileInfo(imgPath).baseName().trimmed() + QStringLiteral(".jpg");

    // rescale image if requested
    int maxDim = m_widget->m_dimensionSpB->value();

    if (m_widget->m_resizeChB->isChecked()
        && (image.width() > maxDim || image.height() > maxDim))
    {
        qCDebug(KIPIPLUGINS_LOG) << "Resizing to " << maxDim;
        image = image.scaled(maxDim, maxDim, Qt::KeepAspectRatio,
                             Qt::SmoothTransformation);
    }

    qCDebug(KIPIPLUGINS_LOG) << "Saving to temp file: " << m_tmpPath;
    image.save(m_tmpPath, "JPEG", m_widget->m_imageQualitySpB->value());

    // copy meta data to temporary image
    KPMetadata meta;

    if (meta.load(imgPath))
    {
        caption = getImageCaption(imgPath);
        meta.setImageDimensions(image.size());
        meta.setImageProgramId(QStringLiteral("Kipi-plugins"), kipipluginsVersion());
        meta.save(m_tmpPath);
    }
    else
    {
        caption.clear();
    }

    return true;
}

void FbWindow::uploadNextPhoto()
{
    if (m_transferQueue.isEmpty())
    {
        setRejectButtonMode(QDialogButtonBox::Close);
        m_widget->progressBar()->hide();
        m_widget->progressBar()->progressCompleted();
        return;
    }

    m_widget->m_imgList->processing(m_transferQueue.first());
    QString imgPath = m_transferQueue.first().toLocalFile();

    m_widget->progressBar()->setMaximum(m_imagesTotal);
    m_widget->progressBar()->setValue(m_imagesCount);

    // check if we have to RAW file -> use preview image then
    bool    isRAW = KPMetadata::isRawFile(QUrl::fromLocalFile(imgPath));
    QString caption;
    bool    res;

    if (isRAW || m_widget->m_resizeChB->isChecked())
    {
        if (!prepareImageForUpload(imgPath, isRAW, caption))
        {
            slotAddPhotoDone(666, i18n("Cannot open file"));
            return;
        }

        res = m_talker->addPhoto(m_tmpPath, m_currentAlbumID, caption);
    }
    else
    {
        caption = getImageCaption(imgPath);
        m_tmpPath.clear();
        res     = m_talker->addPhoto(imgPath, m_currentAlbumID, caption);
    }

    if (!res)
    {
        slotAddPhotoDone(666, i18n("Cannot open file"));
        return;
    }
}

void FbWindow::slotAddPhotoDone(int errCode, const QString& errMsg)
{
    // Remove temporary file if it was used
    if (!m_tmpPath.isEmpty())
    {
        QFile::remove(m_tmpPath);
        m_tmpPath.clear();
    }

    m_widget->m_imgList->processed(m_transferQueue.first(), (errCode == 0));

    if (errCode == 0)
    {
        m_transferQueue.pop_front();
        m_imagesCount++;
    }
    else
    {
        if (KMessageBox::warningContinueCancel(this,
                                               i18n("Failed to upload photo into Facebook: %1\n"
                                                    "Do you want to continue?", errMsg))
            != KMessageBox::Continue)
        {
            setRejectButtonMode(QDialogButtonBox::Close);
            m_widget->progressBar()->hide();
            m_widget->progressBar()->progressCompleted();
            m_transferQueue.clear();
            return;
        }
    }

    uploadNextPhoto();
}

void FbWindow::slotCreateAlbumDone(int errCode, const QString& errMsg, const QString& newAlbumID)
{
    if (errCode != 0)
    {
        KMessageBox::error(this, i18n("Facebook Call Failed: %1", errMsg));
        return;
    }

    // reload album list and automatically select new album
    m_currentAlbumID = newAlbumID;
    m_talker->listAlbums();
}

void FbWindow::slotImageListChanged()
{
    startButton()->setEnabled(!(m_widget->m_imgList->imageUrls().isEmpty()));
}

} // namespace KIPIFacebookPlugin
