/* ============================================================
 * Authors: Renchi Raju <renchi@pooh.tam.uiuc.edu>
 *          Gilles Caulier <caulier dot gilles at kdemail dot net>
 * Date   : 2003-10-14
 * Description : batch image rotation
 * 
 * Copyright 2003-2005 by Renchi Raju
 * Copyright 2006 by Gilles Caulier
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

#ifndef IMAGEROTATE_H
#define IMAGEROTATE_H

// Local includes.

#include "actions.h"

class QString;

namespace KIPIJPEGLossLessPlugin
{

bool rotate(const QString& src, RotateAction angle, const QString& TmpFolder, QString& err);

bool rotateJPEG(const QString& src, const QString& dest, RotateAction angle, QString& err);

bool rotateImageMagick(const QString& src, const QString& dest, RotateAction angle, QString& err);

}  // NameSpace KIPIJPEGLossLessPlugin

#endif /* IMAGEROTATE_H */
