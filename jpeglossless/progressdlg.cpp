/* ============================================================
 * Authors: Renchi Raju <renchi@pooh.tam.uiuc.edu>
 *          Gilles Caulier <caulier dot gilles at kdemail dot net>
 * Date  : 2003-12-11
 * Description : batch progress dialog
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

#include <qlabel.h>
#include <qprogressbar.h>
#include <qlayout.h>
#include <kpushbutton.h>
#include <kapplication.h>
#include <kstdguiitem.h>
#include <klocale.h>

#include "progressdlg.h"

namespace KIPIJPEGLossLessPlugin
{

ProgressDlg::ProgressDlg()
           : QDialog(kapp->activeWindow())
{
    QVBoxLayout *lay = new QVBoxLayout(this, 6, 11);
    label_ = new QLabel(this);
    lay->addWidget(label_);
    bar_   = new QProgressBar(this);
    lay->addWidget(bar_);

    QHBoxLayout *hlay = new QHBoxLayout(lay);
    hlay->addItem(new QSpacerItem(10,10,QSizePolicy::Expanding,
                                  QSizePolicy::Minimum));
    btn_ = new KPushButton(KStdGuiItem::cancel(),this);
    hlay->addWidget(btn_);

    connect(btn_, SIGNAL(clicked()),
            this, SIGNAL(signalCanceled()));
}

ProgressDlg::~ProgressDlg()
{    
}

void ProgressDlg::setText(const QString& text)
{
    label_->setText(text);
}

void ProgressDlg::setProgress(int current, int total)
{
    bar_->setProgress(current, total);
    if (current >= total)
        hide();
}

void ProgressDlg::reset()
{
    bar_->setProgress(0);
    hide();
}

}  // NameSpace KIPIJPEGLossLessPlugin

#include "progressdlg.moc"
