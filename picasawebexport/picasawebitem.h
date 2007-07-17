/* ============================================================
 * File  : picasawebitem.h
 * Author: Vardhman Jain <vardhman @ gmail.com>
 * Date  : 2007-16-07
 * Description : 
 * 
 * Copyright 2007 By Vardhman Jain <vardhman @ gmail.com>

 * This program is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General
 * Public License as published bythe Free Software Foundation;
 * either version 2, or (at your option)
 * any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * ============================================================ */

#ifndef PICASAWEBITEM_H
#define PICASAWEBITEM_H

#include <qstring.h>

namespace KIPIPicasawebExportPlugin
{

class GPhoto
{
public:

    GPhoto()
    {
        //ref_num = -1;
    }
    
    int           ref_num;
    QStrList      tags;
    QString       title;
    QString       description;
    bool 	 is_public;
    bool 	 is_private;
    bool 	 is_family;
    
};    

class FPhotoInfo
{
public:

    FPhotoInfo()
    {
    is_public=false;
    is_family=false;
    is_friend=false;
    }
    
    
    QString       title;
    QString       description;
    QStringList      tags;
    bool 	 is_public;
    bool 	 is_friend;
    bool 	 is_family;
};

class GAlbum
{
public:

    GAlbum()
    {
        ref_num        = -1;
        parent_ref_num = -1;

        add            = false;
        write          = false;
        del_item       = false;
        del_alb        = false;
        create_sub     = false;
    }

    int                ref_num;
    int                parent_ref_num;
    QString            name;
    QString            parentName;
    QString            title;
    QString            summary;
    QString            baseurl;
                       
    bool               add;
    bool               write;
    bool               del_item;
    bool               del_alb;
    bool               create_sub;
};

class PicasaWebAlbum
{
	public:
		PicasaWebAlbum()
		{
			id="-1";
		}
	QString  id;
	QString primary; //="2483" 
	QString secret;//="abcdef"
	QString server;
	QString photos;
	QString title;
	QString description;
};
}
#endif /* PICASAWEBITEM_H */
