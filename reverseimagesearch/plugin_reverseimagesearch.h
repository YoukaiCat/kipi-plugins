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

#ifndef PLUGIN_REVERSEIMAGESEARCH_H
#define PLUGIN_REVERSEIMAGESEARCH_H

// Qt includes

#include <QVariant>
#include <QTemporaryFile>

// Libkipi includes

#include <KIPI/Plugin>

using namespace KIPI;

namespace KIPIReverseImageSearchPlugin
{

class Plugin_ReverseImageSearch : public Plugin
{
    Q_OBJECT

public:

    explicit Plugin_ReverseImageSearch(QObject* const parent, const QVariantList& args);
    ~Plugin_ReverseImageSearch();

    void setup(QWidget* const);

public Q_SLOTS:

    void openInDefaulWebBrowser(QTemporaryFile* file);

private:

    void setupActions();

private:

    class Private;
    Private* const d;
};

} // namespace KIPIReverseImageSearchPlugin

#endif // PLUGIN_REVERSEIMAGESEARCH_H
