/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2003-10-01
 * Description : a kipi plugin to batch process images
 *
 * Copyright (C) 2003-2009 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2005 by Owen Hirst <n8rider@sbcglobal.net>
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

#include "renameimageswidget.h"
#include "renameimageswidget.moc"

// C ANSI includes

extern "C"
{
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
}

// C++ includes

#include <cstdio>
#include <ctime>

// Qt includes

#include <Q3GroupBox>
#include <Q3PopupMenu>
#include <Q3ProgressDialog>
#include <QCheckBox>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QLabel>
#include <QLineEdit>
#include <QPixmap>
#include <QPushButton>
#include <QRegExp>
#include <QSpinBox>
#include <QTimer>
#include <QToolTip>

// KDE includes

#include <kconfig.h>
#include <kdebug.h>
#include <kdeversion.h>
#include <kio/previewjob.h>
#include <kio/renamedialog.h>
#include <klocale.h>

// LibKIPI includes

#include <libkipi/interface.h>
#include <libkipi/imageinfo.h>

// LibKIPI includes

#include "imagedialog.h"

// Local includes

#include "batchprocessimagesitem.h"

namespace KIPIBatchProcessImagesPlugin
{

RenameImagesWidget::RenameImagesWidget(QWidget *parent,
                                       KIPI::Interface* interface,
                                       const KUrl::List& urlList)
    : QWidget(parent),
      m_interface(interface),
      m_urlList(urlList)
{
    setupUi(this);
    readSettings();

    Q3PopupMenu* sortMenu = new Q3PopupMenu(this);
    sortMenu->insertItem(i18n("Sort by Name"), BYNAME);
    sortMenu->insertItem(i18n("Sort by Size"), BYSIZE);
    sortMenu->insertItem(i18n("Sort by Date"), BYDATE);
    m_sortButton->setPopup(sortMenu);

    QToolTip::add(m_useExtraSymbolsCheck,
            "[e] - extension (small one - after last '.')\n"
            "[e-] - extension lower case\n"
            "[e+] extension upper case\n"
            "[i] - sequence number - no leading zeros\n"
            "[i:4] - sequence number in 4 digit with leading zeros format\n"
            "[n] - original file name\n"
            "[n+] - original file name upper case\n"
            "[n-] - original file name lower case\n"
            "[n:5..-2] - substring of original filename from char 5 to second from the end\n"
            "[n+:..5] - whole name (base + extension, characters from 1 to 5)\n"
            "[a] - album name\n"
            "[p+] - absolute path (uppercase)\n"
            "[B:4..-2] - base name (big one - all before last ',', from 4-th to one before last characters)\n"
            "[b-:-3..] - base name (small one - all before first '.', last 3 characters)");

    connect(m_listView, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
            SLOT(slotListViewDoubleClicked(QTreeWidgetItem*)));
    connect(m_listView, SIGNAL(currentItemChanged(QTreeWidgetItem*, QTreeWidgetItem*)),
            SLOT(slotImageSelected(QTreeWidgetItem*)));

    connect(m_prefixEdit, SIGNAL(textChanged(const QString&)),
            SLOT(slotOptionsChanged()));
    connect(m_seqSpin, SIGNAL(valueChanged(int)),
            SLOT(slotOptionsChanged()));
    connect(m_addFileNameCheck, SIGNAL(toggled(bool)),
            SLOT(slotOptionsChanged()));
    connect(m_useExtraSymbolsCheck, SIGNAL(toggled(bool)),
            SLOT(slotOptionsChanged()));
    connect(m_addFileDateCheck, SIGNAL(toggled(bool)),
            SLOT(slotOptionsChanged()));
    connect(m_formatDateCheck, SIGNAL(toggled(bool)),
            SLOT(slotOptionsChanged()));
    connect(m_formatDateEdit, SIGNAL(textChanged(const QString&)),
            SLOT(slotOptionsChanged()));

    connect(m_addButton, SIGNAL(clicked()),
            SLOT(slotAddImages()));
    connect(m_removeButton, SIGNAL(clicked()),
            SLOT(slotRemoveImage()));

	connect(sortMenu, SIGNAL(activated(int)),
			SLOT(sortList(int)) );

	connect(m_reverseList, SIGNAL(clicked()),
			SLOT(reverseList()) );

    connect(m_moveUp, SIGNAL(clicked()),
            SLOT(moveCurrentItemUp()) );

    connect(m_moveDown, SIGNAL(clicked()),
            SLOT(moveCurrentItemDown()) );

    m_timer = new QTimer(this);
    m_progress = new Q3ProgressDialog(this, 0, true);
    connect(m_timer, SIGNAL(timeout()),
            SLOT(slotNext()));
    connect(m_progress, SIGNAL(canceled()),
            SLOT(slotAbort()));

    kDebug() << m_urlList;
    for (KUrl::List::iterator it = m_urlList.begin();
         it != m_urlList.end(); ++it)
    {
        new BatchProcessImagesItem(m_listView,
                                   (*it).path().section('/', 0, -1),
                                   (*it).fileName(),
                                   QString(),
                                   QString());
    }

    updateListing();
}

RenameImagesWidget::~RenameImagesWidget()
{
    delete m_timer;
    delete m_progress;

    saveSettings();
}

void RenameImagesWidget::readSettings()
{
    KConfig config("kipirc");
    KConfigGroup group = config.group("RenameImages Settings");

    m_prefixEdit->setText(group.readEntry("PrefixString", ""));
    m_seqSpin->setValue(group.readEntry("FirstRenameValue", 1));

    m_addFileNameCheck->setChecked(group.readEntry("AddOriginalFileName", false));
    m_useExtraSymbolsCheck->setChecked(group.readEntry("UseExtraSymbolsCheck", false));
    m_addFileDateCheck->setChecked(group.readEntry("AddImageFileDate", false));
    m_formatDateCheck->setChecked(group.readEntry("FormatDate", false));
    m_formatDateEdit->setText(group.readEntry("FormatDateString", "%Y-%m-%d"));

    slotOptionsChanged();
}

void RenameImagesWidget::saveSettings()
{
    KConfig config("kipirc");
    KConfigGroup group = config.group("RenameImages Settings");

    group.writeEntry("PrefixString", m_prefixEdit->text());
    group.writeEntry("FirstRenameValue", m_seqSpin->value());

    group.writeEntry("AddOriginalFileName", m_addFileNameCheck->isChecked());
    group.writeEntry("UseExtraSymbolsCheck", m_useExtraSymbolsCheck->isChecked());
    group.writeEntry("AddImageFileDate", m_addFileDateCheck->isChecked());
    group.writeEntry("FormatDate", m_formatDateCheck->isChecked());
    group.writeEntry("FormatDateString", m_formatDateEdit->text());

    config.sync();
}

void RenameImagesWidget::slotOptionsChanged()
{
    m_formatDateCheck->setEnabled(m_addFileDateCheck->isChecked());
    m_useExtraSymbolsCheck->setEnabled(m_addFileDateCheck->isChecked());
    m_formatDateEdit->setEnabled(m_formatDateCheck->isEnabled() &&
                                 m_formatDateCheck->isChecked());

    updateListing();
}

void RenameImagesWidget::slotListViewDoubleClicked(QTreeWidgetItem*)
{
    // TODO: Implement
}

void RenameImagesWidget::slotImageSelected(QTreeWidgetItem* item)
{
    if (!item)
    {
        m_removeButton->setEnabled(false);
        return;
    }

    m_removeButton->setEnabled(true);
    m_pixLabel->clear();

    BatchProcessImagesItem* it = static_cast<BatchProcessImagesItem*>(item);
    KIO::PreviewJob* thumbJob = KIO::filePreview(KUrl(it->pathSrc()),
                                                 m_pixLabel->height() );

    connect(thumbJob, SIGNAL(gotPreview(const KFileItem*, const QPixmap&)),
            SLOT(slotGotPreview(const KFileItem*, const QPixmap&)));
}


void RenameImagesWidget::sortList(int intSortOrder)
{
    SortOrder sortOrder = static_cast<SortOrder>(intSortOrder);

    QTreeWidgetItemIterator it(m_listView->topLevelItem(0));
    for (; *it; ++it)
    {
        BatchProcessImagesItem* item = static_cast<BatchProcessImagesItem*>(*it);

        switch (sortOrder)
        {
        case(BYNAME):
        {
            item->setKey(item->text(1), false);
            break;
        }
        case(BYSIZE):
        {
            QFileInfo fi(item->pathSrc());
            item->setKey(QString::number(fi.size()), false);
            break;
        }
        case(BYDATE):
        {
            KUrl url(item->pathSrc());
            KIPI::ImageInfo info = m_interface->info(url);
            item->setKey(info.time().toString(Qt::ISODate), false);
            break;
        }
        }
    };

    // FIXME: test
    m_listView->sortItems(-1, Qt::AscendingOrder);

    updateListing();
}


void RenameImagesWidget::reverseList()
{
    if (m_listView->topLevelItemCount() < 2) return;

    QList<QTreeWidgetItem*> lst;
    while (m_listView->topLevelItemCount() > 0) {
        lst.prepend(m_listView->takeTopLevelItem(0));
    }
    m_listView->addTopLevelItems(lst);

    updateListing();
}


void RenameImagesWidget::moveCurrentItemUp() {
    QTreeWidgetItem* currentItem = m_listView->currentItem();
    if (!currentItem) return;

    int index = m_listView->indexOfTopLevelItem(currentItem);
    if (index == 0) {
        return;
    }

    m_listView->takeTopLevelItem(index);
    m_listView->insertTopLevelItem(index - 1, currentItem);
    m_listView->setCurrentItem(currentItem);

    updateListing();
}


void RenameImagesWidget::moveCurrentItemDown() {
    QTreeWidgetItem* currentItem = m_listView->currentItem();
    if (!currentItem) return;

    int index = m_listView->indexOfTopLevelItem(currentItem);
    if (index == m_listView->topLevelItemCount() - 1) {
        return;
    }

    m_listView->takeTopLevelItem(index);
    m_listView->insertTopLevelItem(index + 1, currentItem);
    m_listView->setCurrentItem(currentItem);

    updateListing();
}


void RenameImagesWidget::updateListing()
{
    int pos = 0;
    QTreeWidgetItemIterator it(m_listView);
    for (; *it; ++it)
    {
        BatchProcessImagesItem* item = static_cast<BatchProcessImagesItem*>(*it);
        item->changeNameDest(oldToNewName(item, pos));
        item->changeResult(QString());
        item->changeError(QString());
        item->changeOutputMess(QString());
        pos++;
    }
}

QString RenameImagesWidget::oldToNewName(BatchProcessImagesItem* item,
                                         int itemPosition)
{
    KUrl url;
    url.setPath(item->pathSrc());

    QFileInfo fi(item->pathSrc());

    KIPI::ImageInfo info = m_interface->info(url);

    bool useExtraSymbols = m_addFileDateCheck->isChecked() &&
        m_useExtraSymbolsCheck->isChecked();

    QString newName = m_prefixEdit->text();

    if (m_addFileNameCheck->isChecked())
    {
        newName += fi.baseName();
        newName += "_";
    }

    int seqNumber = itemPosition + m_seqSpin->value();
    if (m_addFileDateCheck->isChecked())
    {
        QString format = m_formatDateEdit->text();
        format = format.simplified();
        if (useExtraSymbols)
        {
            QRegExp rxI("\\[i(:(\\d+))?\\]");
            QRegExp rxN("\\[([anbBeEp])([-+]?)(:(\\d*|-\\d+)\\.\\.(\\d*|-\\d+))?\\]");

            for(int watchDog = 0; watchDog < 100; watchDog++)
            {
                QString to;
                int j, i = rxI.search(format);
                if (i != -1)
                {
                    j = rxI.matchedLength();
                    QString digits = rxI.cap(2);
                    int k = digits.isEmpty() ? 0 : digits.toInt();
                    if (k < 2)
                    {
                        to = QString::number(seqNumber);
                    }
                    else
                    {
                        QString fmt;
                        fmt.sprintf("0%dd", (k > 10 ? 10 : k));
                        fmt = "%" + fmt;
                        to.sprintf(fmt.toLatin1(), seqNumber);
                    }
                }
                else
                {
                    if ((i = rxN.search(format)) == -1)
                    {
                        break;
                    }
                    j = rxN.matchedLength();
                    QString from = rxN.cap(1);
                    from = (from == "e") ? fi.extension(/*complete=*/false) :
                           (from == "E") ? fi.extension(/*complete=*/true) :
                           (from == "b") ? fi.baseName(/*complete=*/false) :
                           (from == "B") ? fi.baseName(/*complete=*/true) :
                           (from == "n") ? fi.fileName() :
                           (from == "a") ? fi.dir(/*absPath=*/true).dirName() :
                           (from == "p") ? fi.absolutePath() :
                           "";
                    int len = from.length();
                    QString start = rxN.cap(4);
                    QString end = rxN.cap(5);
                    int k = start.isEmpty() ? 1 : start.toInt();
                    int l = end.isEmpty() ? len : end.toInt();
                    k = (k < -len) ? 0 : (k < 0) ? (len + k) : (k > 0) ? (k - 1) : 0;
                    l = (l < -len) ? -1 : (l < 0) ? (len + l) : (l > 0) ? (l - 1) : 0;
                    to = l < k ? "" : from.mid(k, l - k + 1);
                    QString changeCase = rxN.cap(2);
                    if (!changeCase.isEmpty())
                    {
                        to = (changeCase == "+") ? to.toUpper() : to.toLower();
                    }
                }
                format.replace(i, j, to);
            }
        }
        format.replace("%%","%");
        format.replace("%s","");
        format.replace("/", "!");
        format.replace("%[","% [");

        time_t time = info.time().toTime_t();
        struct tm* time_tm = ::localtime(&time);
        char s[100];
        ::strftime(s, 100, QFile::encodeName(format), time_tm);

        newName += QString::fromLocal8Bit(s);
        if (!useExtraSymbols)
        {
            newName += "_";
        }
    }

    if (!useExtraSymbols)
    {
        int numDigits = 1;
        int count = m_listView->topLevelItemCount();
        while (count > 0)
        {
            numDigits++;
            count = count / 10;
        }

        QString format;
        format.sprintf("0%dd", numDigits);
        format = "%" + format;

        QString seq;
        seq.sprintf(format.toLatin1(), seqNumber);
        newName += seq;

        newName += QString::fromLatin1(".") + fi.extension();
    }

    return newName;
}

void RenameImagesWidget::slotGotPreview(const KFileItem*, const QPixmap& pix)
{
    m_pixLabel->setPixmap(pix);
}

void RenameImagesWidget::slotStart()
{
    m_timer->start(0, true);

    QTreeWidgetItem* item = m_listView->topLevelItem(0);
    m_listView->setCurrentItem(item);
    m_listView->scrollToItem(item);

    m_progress->setTotalSteps(m_listView->topLevelItemCount());
    m_progress->setProgress(0);
    m_progress->show();

    m_overwriteAll = false;
    m_autoSkip     = false;
}

void RenameImagesWidget::slotAbort()
{
    m_timer->stop();
    m_progress->reset();
    m_progress->hide();
}

void RenameImagesWidget::slotNext()
{
    QTreeWidgetItem* it = m_listView->selectedItems().first();
    if (!it)
    {
        slotAbort();
        return;
    }

    BatchProcessImagesItem* item = static_cast<BatchProcessImagesItem*>(it);
    KUrl src;
    src.setPath(item->pathSrc());
    KUrl dst = src.upUrl();
    dst.addPath(item->text(2));

    bool skip      = false;
    bool overwrite = false;

    if (!m_overwriteAll)
    {
        struct stat info;
        while (::stat(QFile::encodeName(dst.path()), &info) == 0)
        {
            if (m_autoSkip)
            {
                skip = true;
                break;
            }

            KIO::RenameDialog dlg(this, i18n("Rename File"), src.path(), dst.path(),
                                  KIO::RenameDialog_Mode(KIO::M_MULTI | KIO::M_OVERWRITE | KIO::M_SKIP));
            int result = dlg.exec();
            dst        = dlg.newDestUrl();

            switch (result)
            {
            case KIO::R_CANCEL:
            {
                slotAbort();
                return;
            }
            case KIO::R_SKIP:
            {
                skip = true;
                break;
            }
            case KIO::R_AUTO_SKIP:
            {
                m_autoSkip = true;
                skip       = true;
                break;
            }
            case KIO::R_OVERWRITE:
            {
                overwrite       = true;
                break;
            }
            case KIO::R_OVERWRITE_ALL:
            {
                m_overwriteAll = true;
                overwrite      = true;
                break;
            }
            default:
                break;
            }

            if (skip || overwrite)
                break;
        }
    }

    if (skip)
    {
        item->changeResult(i18n("Skipped"));
    }
    else
    {
        // Get the src info
        KIPI::ImageInfo srcInfo = m_interface->info(src);

        if (::rename(QFile::encodeName(src.path()),
                     QFile::encodeName(dst.path())) == 0)
        {
            srcInfo.setTitle(dst.fileName());

            item->changeResult(i18n("OK"));
        }
        else
        {
            item->changeResult(i18n("Failed"));
        }
    }

    m_progress->setProgress(m_progress->progress() + 1);

    it = m_listView->itemBelow(it);
    if (it)
    {
        m_listView->setCurrentItem(it);
        m_listView->scrollToItem(it);
        m_timer->start(0, true);
    }
}

void RenameImagesWidget::slotAddImages()
{
    KUrl::List urls = KIPIPlugins::ImageDialog::getImageURLs(this, m_interface);

    for (KUrl::List::iterator it = urls.begin(); it != urls.end(); ++it)
    {
        if (m_urlList.contains(*it))
            continue;

        new BatchProcessImagesItem(m_listView,
                                   (*it).path().section('/', 0, -1),
                                   (*it).fileName(),
                                   QString(),
                                   QString());
        m_urlList.append(*it);
    }

    updateListing();
}

void RenameImagesWidget::slotRemoveImage()
{
    if (m_listView->selectedItems().isEmpty())
        return;

    BatchProcessImagesItem* item =
        static_cast<BatchProcessImagesItem*>(m_listView->selectedItems().first());
    delete item;

    m_pixLabel->clear();

    updateListing();
}

}  // namespace KIPIBatchProcessImagesPlugin
