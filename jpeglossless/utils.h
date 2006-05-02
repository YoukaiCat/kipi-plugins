/* ============================================================
 * Authors: Renchi Raju <renchi@pooh.tam.uiuc.edu>
 *          Gilles Caulier <caulier dot gilles at kdemail dot net>
 * Date   : 2003-12-03
 * Description : misc utils to used in batch process
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

#ifndef UTILS_H
#define UTILS_H

class QString;

namespace KIPIJPEGLossLessPlugin
{

/** Test if a file is a JPEG file
 */

bool isJPEG(const QString& file);

/** POSIX Compliant File Copy and Move -
    Can't use KIO based operations as we need to use these in a thread
*/

bool CopyFile(const QString& src, const QString& dst);

bool MoveFile(const QString& src, const QString& dst);

}  // NameSpace KIPIJPEGLossLessPlugin

#endif /* UTILS_H */
