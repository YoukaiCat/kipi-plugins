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

#ifndef REVERSEIMAGESEARCHENGINE_H
#define REVERSEIMAGESEARCHENGINE_H

// Qt includes

#include <QTemporaryFile>

// Local includes

#include "kpmultipart.h"

namespace KIPIReverseImageSearchPlugin
{

class ReverseImageSearchEngine : public QObject
{
    Q_OBJECT

public:

    explicit ReverseImageSearchEngine(QString name, QObject* parent);

Q_SIGNALS:

    void ready(QTemporaryFile* file);

public Q_SLOTS:

    void find(QString filepath);

private:

    QString name;
};

} // namespace KIPIReverseImageSearchPlugin

#endif // REVERSEIMAGESEARCHENGINE_H
