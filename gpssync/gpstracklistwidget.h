/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.kipi-plugins.org
 *
 * Date        : 2008-02-08
 * Description : a widget to display a GPS track list over web map locator.
 *
 * Copyright (C) 2008 by Gilles Caulier <caulier dot gilles at gmail dot com>
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

#ifndef GPSTRACKLISTWIDGET_H
#define GPSTRACKLISTWIDGET_H

// Qt includes.

#include <QString>

// KDE includes.

#include <khtml_part.h>

namespace KIPIGPSSyncPlugin
{

class GPSTrackListWidgetPrivate;

class GPSTrackListWidget : public KHTMLPart
{
    Q_OBJECT

public:

    GPSTrackListWidget(QWidget* parent);
    ~GPSTrackListWidget();

    void    setGPSPosition(const QString& lat, const QString& lon);
    void    GPSPosition(QString& lat, QString& lon);

    void    setZoomLevel(int zoomLevel);
    int     zoomLevel();

    void    setMapType(const QString& mapType);
    QString mapType();

    void    setFileName(const QString& fileName);
    QString fileName();

    void    resized();

signals:

    void signalNewGPSLocationFromMap(const QString&, const QString&);

protected:

    void khtmlMouseReleaseEvent(khtml::MouseReleaseEvent *);

private:

    GPSTrackListWidgetPrivate *d;
};

}  // namespace KIPIGPSSyncPlugin

#endif /* GPSTRACKLISTWIDGET_H */
