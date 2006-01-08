/* ============================================================
 * File  : simpleviewerexport.cpp
 * Author: Joern Ahrens <joern.ahrens@kdemail.net>
 * Date  : 2005-12-19
 * Description :
 *
 * Copyright 2005-2006 by Joern Ahrens
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */

// QT includes

#include <qtimer.h>
#include <qimage.h>
#include <qtextstream.h>
#include <qfile.h>
#include <qdir.h>

// KDE includes

#include <kdebug.h>
#include <klocale.h>
#include <kapplication.h>
#include <kio/netaccess.h>
#include <kfilemetainfo.h>
#include <kstandarddirs.h>
#include <kio/job.h>
#include <kzip.h>
#include <kmessagebox.h>

// KIPI includes

#include <libkipi/version.h>
#include <libkipi/batchprogressdialog.h>
#include <libkipi/imageinfo.h>

// Local includes

#include "simpleviewerexport.h"
#include "firstrundlg.h"
#include "svedialog.h"

namespace KIPISimpleViewerExportPlugin
{
    
// maxium size of a simpleviewer thumbnail
// TODO: read from configfile
const int maxThumbSize = 45;
const QString viewer("viewer.swf");
    
void SimpleViewerExport::run(KIPI::Interface* interface, QObject *parent)
{
    SimpleViewerExport *plugin = new SimpleViewerExport(interface, parent);
 
    if(!plugin->checkSimpleViewer())
    {
        if(!plugin->installSimpleViewer())
        {
            return;
        }
    }
    
    if(plugin->configure())
        plugin->startExport();
    
    delete plugin;
}
    
SimpleViewerExport::SimpleViewerExport(KIPI::Interface* interface, QObject *parent)
    : QObject(parent)
{
    m_interface = interface;
    m_configDlg = 0;
    m_canceled = true;
    m_dataLocal = locateLocal("data", "kipiplugin_simpleviewerexport/simpleviewer/", true);
    
    m_simpleViewerFiles.append(viewer);
    m_simpleViewerFiles.append("flash_detect.js");
    m_simpleViewerFiles.append("get_flash_player.gif");
}

SimpleViewerExport::~SimpleViewerExport()
{

}

bool SimpleViewerExport::configure()
{
    m_canceled = false;
    
    if(!m_configDlg)
        m_configDlg = new SVEDialog(m_interface, kapp->activeWindow());

    bool configured = false;
    while(!configured)
    {
        if(m_configDlg->exec() == QDialog::Rejected)
            return false;
    
        configured = true;
        
        if(KIO::NetAccess::exists(m_configDlg->exportURL(), false, kapp->activeWindow()))
        {
            int ret = KMessageBox::warningYesNoCancel(kapp->activeWindow(),
                                                      i18n("Target folder %1 already exists.\n"
                                                           "Do you want to overwrite it (all data in this folder will be lost)")
                                                           .arg(m_configDlg->exportURL()));
            
            switch(ret)
            {
                case KMessageBox::Yes:
                    if(!KIO::NetAccess::del(m_configDlg->exportURL(), kapp->activeWindow()))
                    {
                        KMessageBox::error(kapp->activeWindow(), i18n("Could not delete %1\n"
                                "Please choose another export folder").arg(m_configDlg->exportURL()));
                        configured = false;
                    }
                    break;
                
                case KMessageBox::No:
                    configured = false;
                    break;
                
                case KMessageBox::Cancel:
                    return false;
                    break;
            };
        }
    }
    
    return true;
}

void SimpleViewerExport::startExport()
{
    if(m_canceled)
        return;
    
    m_progressDlg = new KIPI::BatchProgressDialog(kapp->activeWindow(),
                                                  i18n("Simple Viewer Export"));
        
    connect(m_progressDlg, SIGNAL(cancelClicked()),
            this, SLOT(slotCancel()));

    m_progressDlg->show();
    kapp->processEvents();
    // Estimate the number of actions for the KIPI progress dialog.
    m_progressDlg->addedAction(i18n("Estimate the number of actions to do..."), KIPI::StartingMessage);
    m_albumsList = m_configDlg->getSelectedAlbums();
    m_totalActions = 0;
    for( QValueList<KIPI::ImageCollection>::Iterator it = m_albumsList.begin() ;
         !m_canceled && (it != m_albumsList.end()) ; ++it )
    {
        m_totalActions += (*it).images().count();
    }
    
    m_progressDlg->setProgress(0, m_totalActions);

    slotProcess();

#if KDE_VERSION >= 0x30200
           m_progressDlg->setButtonCancel(KStdGuiItem::close());
#else
           m_progressDlg->setButtonCancelText(i18n("&Close"));
#endif

}

void SimpleViewerExport::slotCancel()
{
    m_canceled = true;
}

void SimpleViewerExport::slotProcess()
{
    if(m_canceled)
        return;
    
    m_progressDlg->addedAction(i18n("Initialising..."), KIPI::StartingMessage);
    if(!createExportDirectories())
    {
            m_progressDlg->addedAction(i18n("Failed to create export directories"),
                                       KIPI::ErrorMessage);
        return;
    }

    m_progressDlg->addedAction(i18n("Creating images and thumbnails..."), KIPI::StartingMessage);
    if(!exportImages())
    {
        m_progressDlg->addedAction(i18n("Failed to export the images"),
                                   KIPI::ErrorMessage);
        return;
    }
    m_progressDlg->addedAction(i18n("Finished creating images and thumbnails..."), KIPI::SuccessMessage);
}

bool SimpleViewerExport::createExportDirectories()
{
    KURL root = m_configDlg->exportURL();
    
    if(!KIO::NetAccess::mkdir(root, kapp->activeWindow()))
    {
        m_progressDlg->addedAction(i18n("Could not create folder '%1'").arg(root.url()),
                                   KIPI::ErrorMessage);
        return(false);
    }
    
    KURL thumbsDir = root;
    thumbsDir.addPath("/thumbs");
    if(!KIO::NetAccess::mkdir(thumbsDir, kapp->activeWindow()))
    {
        m_progressDlg->addedAction(i18n("Could not create folder '%1'").arg(thumbsDir.url()),
                                   KIPI::ErrorMessage);
        return(false);
    }

    KURL imagesDir = root;
    imagesDir.addPath("/images");
    if(!KIO::NetAccess::mkdir(imagesDir, kapp->activeWindow()))
    {
        m_progressDlg->addedAction(i18n("Could not create folder '%1'").arg(imagesDir.url()),
                                   KIPI::ErrorMessage);
        return(false);
    }
    
    return true;
}

bool SimpleViewerExport::exportImages()
{
    KURL thumbsDir(m_configDlg->exportURL());
    thumbsDir.addPath("/thumbs");
    
    KURL imagesDir(m_configDlg->exportURL());
    imagesDir.addPath("/images");

    KURL xmlFile = m_configDlg->exportURL();
    xmlFile.addPath("/imageData.xml");
    QFile file(xmlFile.path());
    file.open(IO_WriteOnly);
    QTextStream ts(&file);
    cfgCreateHeader(ts);

    int action = 0;
    int maxSize = m_configDlg->imagesExportSize();
    bool resizeImages = m_configDlg->resizeExportImages();
    for( QValueList<KIPI::ImageCollection>::Iterator it = m_albumsList.begin() ;
         !m_canceled && (it != m_albumsList.end()) ; ++it )
    {
        KURL::List images = (*it).images();
        for(KURL::List::Iterator it = images.begin();
            !m_canceled && (it != images.end()) ; ++it)
        {
            kapp->processEvents();

            KURL kurl = *it;
            m_progressDlg->addedAction(i18n("Processing %1").arg((*it).url()),
                                       KIPI::StartingMessage);
            QImage image;
            if(!image.load(kurl.path()))
            {
                m_progressDlg->addedAction(i18n("Could not open image '%1'").arg(kurl.path()),
                                           KIPI::WarningMessage);
                continue;
            }

            QImage thumbnail;
            if(!createThumbnail(image, thumbnail))
            {
                m_progressDlg->addedAction(i18n("Could not create thumbnail from '%1'").arg(kurl.path()),
                                           KIPI::WarningMessage);
                continue;
            }

            if(resizeImages && !resizeImage(image, maxSize, image))
            {
                m_progressDlg->addedAction(i18n("Could not resize image '%1'").arg(kurl.path()),
                                           KIPI::WarningMessage);
                continue;
            }

            KURL thumbnailPath(thumbsDir);
            thumbnailPath.addPath(kurl.filename());
            thumbnail.save(thumbnailPath.path(), "JPEG");

            KURL imagePath(imagesDir);
            imagePath.addPath(kurl.filename());
            image.save(imagePath.path(), "JPEG");

            cfgAddImage(ts, kurl);
            m_progressDlg->setProgress(++action, m_totalActions);
        }
        cfgCreateFooter(ts);
    }
    
    copySimpleViewer();
    
    return true;
}

bool SimpleViewerExport::createThumbnail(const QImage &image, QImage &thumbnail)
{
    int w = image.width();
    int h = image.height();

    int maxSize;

    if(w > maxThumbSize || h > maxThumbSize)
    {
        if(w > h)
        {
            maxSize = (int)(double)(w * maxThumbSize) / h;
        }
        else
        {
            maxSize = (int)(double)(h * maxThumbSize) / w;
        }
    }
    
    maxSize = (maxSize < maxThumbSize) ? maxThumbSize : maxSize;
    
    return resizeImage(image, maxSize, thumbnail);
}

bool SimpleViewerExport::resizeImage(const QImage &image, int maxSize, QImage &resizedImage)
{
    int w = image.width();
    int h = image.height();

    if(w > maxSize || h > maxSize)
    {
        if(w > h)
        {
            h = (int)(double)(h * maxSize) / w;
            h = (h == 0) ? 1 : h;
            w = maxSize;
        }
        else
        {
            w = (int)(double)(w * maxSize) / h;
            w = (w == 0) ? 1 : w;
            h = maxSize;
        }
        resizedImage = image.smoothScale(w, h);
    }

    return true;
}

void SimpleViewerExport::cfgCreateHeader(QTextStream &ts)
{
    ts << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << endl;
    ts << "<SIMPLEVIEWER_DATA"
       << " maxImageDimension=\"" << m_configDlg->maxImageDimension() << "\""
       << " textColor=\"" << m_configDlg->textColor().name().replace("#", "0x") << "\""
       << " frameColor=\"" << m_configDlg->frameColor().name().replace("#", "0x") << "\""
       << " bgColor=\"" << m_configDlg->backgroundColor().name().replace("#", "0x") << "\""
       << " frameWidth=\"" << m_configDlg->frameWidth() << "\""
       << " stagePadding=\"" << m_configDlg->stagePadding() << "\""
       << " thumbnailColumns=\"" << m_configDlg->thumbnailColumns() << "\""
       << " thumbnailRows=\"" << m_configDlg->thumbnailRows() << "\""
       << " navPosition=\"" << m_configDlg->navPosition() << "\""
       << " navDirection=\"" << m_configDlg->navDirection() << "\""
       << " title=\"" << m_configDlg->title() << "\""
       << " imagePath=\"\" thumbPath=\"\">" << endl;
}

void SimpleViewerExport::cfgAddImage(QTextStream &ts, const KURL &kurl)
{
    QString comment;

    if(m_configDlg->showExifComments())
    {
        KIPI::ImageInfo info = m_interface->info(kurl);
        comment = info.description();
    }
    else
    {
        comment = "";
    }

    ts << "<IMAGE>" << endl;
    ts << "<NAME>" << kurl.filename() << "</NAME>" << endl;
    ts << "<CAPTION>" <<  comment  <<  "</CAPTION>" << endl;
    ts << "</IMAGE>" << endl;
}

void SimpleViewerExport::cfgCreateFooter(QTextStream &ts)
{
    ts << "</SIMPLEVIEWER_DATA>" << endl;
}

void SimpleViewerExport::copySimpleViewer()
{
    QString dataDir = locate("data", "kipiplugin_simpleviewerexport/simpleviewer/");
    if(dataDir.isEmpty())
        installSimpleViewer();
    if(dataDir.isEmpty())
        return;
    
    QDir dir(dataDir);
    QStringList files = dir.entryList(QDir::Files);
    for(QStringList::Iterator it = files.begin(); it != files.end(); ++it) 
    {
        *it = dir.absPath() + "/" + *it;
    }
    // TODO: catch errors
    KIO::CopyJob *copyJob = KIO::copy(files, m_configDlg->exportURL(), true);
    
    dataDir = locate("data", "kipiplugin_simpleviewerexport/simpleviewer_html/");
    QDir dirHtml(dataDir);
    QStringList filesHtml = dirHtml.entryList(QDir::Files);
    for(QStringList::Iterator it = filesHtml.begin(); it != filesHtml.end(); ++it) 
    {
        *it = dirHtml.absPath() + "/" + *it;
    }
    // TODO: catch errors
    KIO::CopyJob *copyJob2 = KIO::copy(filesHtml, m_configDlg->exportURL(), true);
}

bool SimpleViewerExport::checkSimpleViewer() const
{
    return ! locate("data", "kipiplugin_simpleviewerexport/simpleviewer/"+viewer).isEmpty();
}

bool SimpleViewerExport::installSimpleViewer()
{
    FirstRunDlg *firstRunDlg = new FirstRunDlg(kapp->activeWindow());
    if(firstRunDlg->exec() == QDialog::Accepted)
    {
        QString url = firstRunDlg->getURL();
        delete firstRunDlg;
        
        if(unzip(url))
        {
            return true;
        }
        else
        {
            // ErrorMessage
        }
    }
    
    return false;
}

bool SimpleViewerExport::unzip(const QString &url)
{
    KZip zip(url);
    
    if(!openArchive(zip))    
    {
        return false;
    }
    
    return extractArchive(zip);
}

bool SimpleViewerExport::openArchive(KZip &zip)
{
    if(!zip.open(IO_ReadOnly))
    {
        kdDebug() << "open archive failed\n";
        return false;
    }
    return true;
}

bool SimpleViewerExport::extractArchive(KZip &zip)
{
    // read root directory content
    QStringList names = zip.directory()->entries();
    if(names.count() != 1)
    {
        kdDebug() << "Wrong SimpleViewer Version or corrupted archive" << endl;
        kdDebug() << "Content of the archive root folder" << names << endl;
        return false;
    }
            
    // open root directory
    const KArchiveEntry *root = zip.directory()->entry(names[0]);
    if(!root || !root->isDirectory())
    {
        kdDebug() << "could not open " << names[0] << " of zipname" << endl;
        return false;
    }
    
    const KArchiveDirectory *dir = dynamic_cast<const KArchiveDirectory*>(root);
            
    // extract the needed files from SimpleViewer archive
    for(QStringList::Iterator it = m_simpleViewerFiles.begin(); 
        it != m_simpleViewerFiles.end(); ++it ) 
    {
        const KArchiveEntry *entry = dir->entry(*it);
        if(!extractFile(entry))
        {
            //TODO error msg
            kdDebug() << "could not open " << *it << " of zipname" << endl;
            return false;
        }
    }
    
    return true;
}

bool SimpleViewerExport::extractFile(const KArchiveEntry *entry)
{
    if( !entry || !entry->isFile() ) 
        return false;
   
    const KArchiveFile *entryFile = dynamic_cast<const KArchiveFile*>(entry);
    QByteArray array = entryFile->data();

    QFile file( m_dataLocal + entry->name() );
    if(file.open( IO_WriteOnly )) 
    {
        int ret = file.writeBlock(array);
        file.close();
        return ret > 0 ? true : false;
    }
    
    return false;
}

} // namespace KIPISimpleViewerExportPlugin

#include "simpleviewerexport.moc"
