/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.digikam.org
 *
 * Date        : 2007-02-11
 * Description : a kipi plugin to show image using
 *               an OpenGL interface.
 *
 * Copyright (C) 2007-2008 by Markus Leuthold <kusi at forum dot titlis dot org>
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

#ifndef VIEWERWIDGET_H
#define VIEWERWIDGET_H

// C++ includes

#include <iostream>

// Qt includes

#include <QCursor>
#include <QDir>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QTimer>
#include <QWheelEvent>

// KDE includes

#include <kurl.h>
#include <kmimetype.h>

// LibKIPI includes

#include <libkipi/imagecollection.h>
#include <libkipi/interface.h>

// Local includes

#include "texture.h"

/**
 * @short OpenGL widget for image viewer
 * @author Markus Leuthold <kusi (+at) forum.titlis.org>
 * @version 0.2
 */

//keep in mind that one cache entry takes 20MB for a 5mpix pic
#define CACHESIZE 4
#define EMPTY 99999

using namespace KIPI;
using namespace std;

namespace KIPIViewerPlugin
{

enum OGLstate
{
    oglOK,
    oglNoRectangularTexture,
    oglNoContext
};

class ViewerWidget : public QGLWidget
{
    Q_OBJECT

public:

    ViewerWidget(Interface* const);
    ~ViewerWidget();

    void     drawImage(Texture* const tex);
    void     downloadTex(Texture* const tex);
    Texture* loadImage(int file_index);
    void     prevImage();
    void     nextImage();
    bool     listOfFilesIsEmpty() const;
    void     zoom(int mdelta, const QPoint& pos, float factor);
    OGLstate getOGLstate();

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);
    virtual void paintGL();
    virtual void mouseReleaseEvent(QMouseEvent* e);
    virtual void keyReleaseEvent(QKeyEvent* e);

protected:

    struct Cache
    {
        int      file_index;
        Texture* texture;
    };

    enum WheelAction
    {
        zoomImage,
        changeImage
    };

protected:

    Texture*         texture;
    unsigned int     old_file_idx, file_idx, idx, oldidx;
    float            ratio_view_y, ratio_view_x, delta;
    QTime            timer;
    QDir             directory;
    QStringList      files;
    unsigned char*   imageJPEGLIB;
    Cache            cache[CACHESIZE];
    GLuint           tex[3];
    float            vertex_height, vertex_width, vertex_left, vertex_top, vertex_right, vertex_bottom;
    QPoint           startdrag, previous_pos;
    WheelAction      wheelAction;
    bool             firstImage;
    QSize            zoomsize;
    QTimer           timerMouseMove;
    QCursor          moveCursor, zoomCursor;
    float            zoomfactor_scrollwheel,  zoomfactor_mousemove,  zoomfactor_keyboard;
    QString          nullImage;
    int              screen_width;
    Interface*       kipiInterface;

protected:

    bool isReallyFullScreen() const;

    virtual void keyPressEvent(QKeyEvent* k);
    virtual void wheelEvent(QWheelEvent* e);
    virtual void mouseMoveEvent(QMouseEvent* e);
    virtual void mousePressEvent(QMouseEvent* e);
    virtual void mouseDoubleClickEvent(QMouseEvent* e);

private Q_SLOTS:

    void timeoutMouseMove();
};

} // namespace KIPIViewerPlugin

#endif // VIEWERWIDGET_H
