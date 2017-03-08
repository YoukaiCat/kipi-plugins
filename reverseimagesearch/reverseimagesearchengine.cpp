/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2017-03-09
 * Description : a tool to use reverse image search engines api
 *
 * Copyright (C) 2017 Vladislav Mileshkin
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

// Qt includes

#include <QFileInfo>
#include <QMimeDatabase>
#include <QStandardPaths>

// Local includes

#include "kipiplugins_debug.h"
#include "reverseimagesearchengine.h"

namespace KIPIReverseImageSearchPlugin
{

ReverseImageSearchEngine::ReverseImageSearchEngine(QString name, QObject* const parent)
    : QObject(parent),
      name(name)
{}

void ReverseImageSearchEngine::find(QString imagePath)
{
    QFile imageFile(imagePath);

    QFileInfo imageFileInfo(imageFile);
    QString fileName = imageFileInfo.fileName();

    if (!imageFile.open(QIODevice::ReadOnly))
    {
        qCDebug(KIPIPLUGINS_LOG) << "Could not open image file: "
                                 << imagePath;
        return;
    }

    QByteArray fileContent = imageFile.readAll();
    QString base64FileContent = QString::fromUtf8(fileContent.toBase64());
    imageFile.close();

    QMimeDatabase db;
    QString fileMimetype = db.mimeTypeForData(fileContent).name();

    QString commonJSName = QLatin1String("kipiplugin_reverseimagesearch/common.js");
    QString commonJSPath = QStandardPaths::locate(QStandardPaths::GenericDataLocation, commonJSName);

    QString templateName = QString::fromLatin1("kipiplugin_reverseimagesearch/%1.html.template").arg(name);
    QString templatePath = QStandardPaths::locate(QStandardPaths::GenericDataLocation,
                                                  templateName);

    QFile templateFile(templatePath);

    if (!templateFile.open(QIODevice::ReadOnly))
    {
        qCDebug(KIPIPLUGINS_LOG) << "Could not open template file: "
                                 << templatePath;
        return;
    }

    QTextStream in(&templateFile);
    QString templateContent = in.readAll();
    templateFile.close();

    templateContent.replace(QLatin1String("#{COMMONJSFILE}#"), commonJSPath);
    templateContent.replace(QLatin1String("#{FILENAME}#"), fileName);
    templateContent.replace(QLatin1String("#{MIMETYPE}#"), fileMimetype);
    templateContent.replace(QLatin1String("#{FILECONTENT}#"), base64FileContent);

    QTemporaryFile * resultHTMLFile = new QTemporaryFile();

    if (!resultHTMLFile->open())
    {
        qCDebug(KIPIPLUGINS_LOG) << "Could not open temporary file";
        return;
    }

    resultHTMLFile->write(templateContent.toUtf8());
    emit ready(resultHTMLFile);
}

} // namespace KIPIReverseImageSearchPlugins

#include "reverseimagesearchengine.moc"
