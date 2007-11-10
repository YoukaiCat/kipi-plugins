/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2007-11-09
 * Description : a class to resize image in a separate thread.
 *
 * Copyright (C) 2007 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef IMAGERESIZE_H
#define IMAGERESIZE_H

// Qt includes.

#include <QThread>
#include <QString>
#include <QStringList>

// KDE includes.

#include <kurl.h>

// Local includes.

#include "emailsettingscontainer.h"

namespace KIPISendimagesPlugin
{

class ImageResizePriv;

class ImageResize : public QThread
{
    Q_OBJECT

public:

    ImageResize(QObject *parent);
    ~ImageResize();

    void resize(const EmailSettingsContainer& settings);
    void cancel();

private:

    void run();
    bool imageResize(const EmailSettingsContainer& settings, 
                     const KUrl& src, const QString& destName, QString& err);

signals:

    void startingResize(const KUrl &fileUrl);
    void finishedResize(const KUrl &fileUrl, const QString& resizedImgPath);
    void failedResize(const KUrl &fileUrl, const QString &errString);
    void completeResize();

private:

    ImageResizePriv *d;
};

}  // NameSpace KIPISendimagesPlugin

#endif /* IMAGERESIZE_H */
