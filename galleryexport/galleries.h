/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Copyright (C) 2003-2005 by Renchi Raju <renchi@pooh.tam.uiuc.edu>
 * Copyright (C) 2006 by Colin Guthrie <kde@colin.guthr.ie>
 * Copyright (C) 2006-2008 by Gilles Caulier <caulier dot gilles at gmail dot com>
 * Copyright (C) 2008 by Andrea Diamantini <adjam7 at gmail dot com>
 *
 *
 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published by the Free Software Foundation;
 * either version 2, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * ============================================================ */



#ifndef GALLERIES_H
#define GALLERIES_H

// Qt includes
#include <QList>
#include <QTreeWidget>

namespace KWallet
{
class Wallet;
}

namespace KIPIGalleryExportPlugin
{

class Gallery
{
public:

    Gallery();
    ~Gallery();

    QString name()           const;
    QString url()            const;
    QString username()       const;
    QString password()       const;
    unsigned int version()   const;
    unsigned int galleryId() const;

    void setName(QString name);
    void setUrl(QString url);
    void setUsername(QString username);
    void setPassword(QString password);
    void setVersion(unsigned int version);
    void setGalleryId(unsigned int galleryId);

private:

    QString mName;
    QString mUrl;
    QString mUsername;
    QString mPassword;
    unsigned int mVersion;
    unsigned int mGalleryId;

public:

    void save();

private:

    void load();
    KWallet::Wallet* mpWallet;

};

}

#endif /* GALLERIES_H */
