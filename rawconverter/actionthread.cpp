/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2003-12-03
 * Description : a class to manage plugin actions using threads
 *
 * Copyright (C) 2003-2005 by Renchi Raju <renchi@pooh.tam.uiuc.edu>
 * Copyright (C) 2006-2007 by Gilles Caulier <caulier dot gilles at gmail dot com>
 *
 * NOTE: Do not use kdDebug() in this implementation because 
 *       it will be multithreaded. Use qDebug() instead. 
 *       See B.K.O #133026 for details.
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * ============================================================ */

// C Ansi includes.

extern "C"
{
#include <unistd.h>
}

// Qt includes.

#include <QApplication>
#include <QDir>
#include <QtDebug>

// KDE includes.

#include <klocale.h>
#include <kstandarddirs.h>

// LibKDcraw includes.

#include <libkdcraw/dcrawinfocontainer.h>

// Local includes.

#include "actionthread.h"

namespace KIPIRawConverterPlugin
{

ActionThread::ActionThread(QObject *parent)
            : QThread(), m_parent(parent)
{
}

ActionThread::~ActionThread()
{
    // cancel the thread
    cancel();
    // wait for the thread to finish
    wait();
}

void ActionThread::cancel()
{
    m_taskQueue.flush();
    m_dcrawIface.cancel();
}

void ActionThread::setRawDecodingSettings(KDcrawIface::RawDecodingSettings rawDecodingSettings, 
                                          SaveSettingsWidget::OutputFormat outputFormat)
{
    m_rawDecodingSettings = rawDecodingSettings;
    m_outputFormat        = outputFormat;
}

void ActionThread::processRawFile(const KUrl& url)
{
    KUrl::List oneFile;
    oneFile.append(url);
    processRawFiles(oneFile);
}

void ActionThread::processHalfRawFile(const KUrl& url)
{
    KUrl::List oneFile;
    oneFile.append(url);
    processHalfRawFiles(oneFile);
}

void ActionThread::identifyRawFile(const KUrl& url, bool full)
{
    KUrl::List oneFile;
    oneFile.append(url);
    identifyRawFiles(oneFile, full);
}

void ActionThread::identifyRawFiles(const KUrl::List& urlList, bool full)
{
    for (KUrl::List::const_iterator it = urlList.begin();
         it != urlList.end(); ++it ) 
    {
        Task *t     = new Task;
        t->filePath = (*it).path();
        t->action   = full ? IDENTIFY_FULL : IDENTIFY;
        m_taskQueue.enqueue(t);
    }
}

void ActionThread::processRawFiles(const KUrl::List& urlList)
{
    for (KUrl::List::const_iterator it = urlList.begin();
         it != urlList.end(); ++it ) 
    {
        Task *t             = new Task;
        t->filePath         = (*it).path();
        t->outputFormat     = m_outputFormat;
        t->decodingSettings = m_rawDecodingSettings;
        t->action           = PROCESS;
        m_taskQueue.enqueue(t);
    }
}

void ActionThread::processHalfRawFiles(const KUrl::List& urlList)
{
    for (KUrl::List::const_iterator it = urlList.begin();
         it != urlList.end(); ++it ) 
    {
        Task *t             = new Task;
        t->filePath         = (*it).path(); //deep copy
        t->outputFormat     = m_outputFormat;
        t->decodingSettings = m_rawDecodingSettings;
        t->action           = PREVIEW;
        m_taskQueue.enqueue(t);
    }
}

void ActionThread::run()
{
    while (!m_taskQueue.isEmpty()) 
    {
        Task *t = m_taskQueue.dequeue();
        if (!t) continue;

        QString errString;

        EventData *d = new EventData;

        switch (t->action) 
        {
            case IDENTIFY: 
            case IDENTIFY_FULL: 
            {
                // Get embedded RAW file thumbnail.
                QImage image;
                m_dcrawIface.loadDcrawPreview(image, t->filePath);

                // Identify Camera model.    
                KDcrawIface::DcrawInfoContainer info;
                m_dcrawIface.rawFileIdentify(info, t->filePath);

                QString identify = i18n("Cannot identify Raw image");
                if (info.isDecodable)
                {
                    if (t->action == IDENTIFY)
                        identify = info.make + QString("-") + info.model;
                    else
                    {
                        identify = i18n("Make: %1\n", info.make); 
                        identify.append(i18n("Model: %1\n", info.model));

                        if (info.dateTime.isValid())
                        {
                            identify.append(i18n("Created: %1\n",
                                     KGlobal::locale()->formatDateTime(info.dateTime,
                                                                       KLocale::ShortDate, true)));
                        }

                        if (info.aperture != -1.0)
                        {
                            identify.append(i18n("Aperture: f/%1\n", QString::number(info.aperture)));
                        }

                        if (info.focalLength != -1.0)
                        {
                            identify.append(i18n("Focal: %1 mm\n", info.focalLength));
                        }                        

                        if (info.exposureTime != -1.0)
                        {
                            identify.append(i18n("Exposure: 1/%1 s\n", info.exposureTime));
                        }
   
                        if (info.sensitivity != -1)
                        {
                            identify.append(i18n("Sensitivity: %1 ISO", info.sensitivity));
                        }
                    }
                }

                EventData *r = new EventData;
                r->action    = t->action;
                r->filePath  = t->filePath;
                r->image     = image;
                r->message   = identify;
                r->success   = true;
                QApplication::postEvent(m_parent, r);
                break;
            }

            case PREVIEW: 
            {
                d->action    = PREVIEW;
                d->filePath  = t->filePath;
                d->starting  = true;
                QApplication::postEvent(m_parent, d);

                QString destPath;
                bool result  = m_dcrawIface.decodeHalfRAWImage(t->filePath, destPath, 
                                                               t->outputFormat, t->decodingSettings);

                EventData *r = new EventData;
                r->action    = PREVIEW;
                r->filePath  = t->filePath;
                r->destPath  = destPath;
                r->success   = result;
                QApplication::postEvent(m_parent, r);
                break;
            }

            case PROCESS: 
            {
                d->action    = PROCESS;
                d->filePath  = t->filePath;
                d->starting  = true;
                QApplication::postEvent(m_parent, d);

                QString destPath;
                bool result  = m_dcrawIface.decodeRAWImage(t->filePath, destPath, 
                                                           t->outputFormat, t->decodingSettings);

                EventData *r = new EventData;
                r->action    = PROCESS;
                r->filePath  = t->filePath;
                r->destPath  = destPath;
                r->success   = result;
                QApplication::postEvent(m_parent, r);
                break;
            }

            default: 
            {
                qCritical() << "KIPIRawConverterPlugin:ActionThread: "
                            << "Unknown action specified"
                            << endl;
                delete d;
            }
        }

        delete t;
    }
}

}  // NameSpace KIPIRawConverterPlugin
