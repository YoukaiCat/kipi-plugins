/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.digikam.org
 *
 * Date        : 2012-04-04
 * Description : a kipi plugin to show image using an OpenGL interface.
 *
 * Copyright (C) 2012-2017 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef HELPDIALOG_H
#define HELPDIALOG_H

// Local includes

#include "kptooldialog.h"

using namespace KIPIPlugins;

namespace KIPIViewerPlugin
{

class HelpDialog : public KPToolDialog
{

public:

    HelpDialog();
    ~HelpDialog();
};

} // namespace KIPIViewerPlugin

#endif /* HELPDIALOG_H */
