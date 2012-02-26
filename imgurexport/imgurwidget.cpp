/* ============================================================
 *
 * This file is a part of kipi-plugins project
 * http://www.digikam.org
 *
 * Date        : 2012-02-12
 * Description : a kipi plugin to export images to the Imgur web service
 *
 * Copyright (C) 2012-2012 by Marius Orcsik <marius at habarnam dot ro>
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

// Qt
#include <QBoxLayout>

// local
#include "imgurwidget.h"

using namespace KIPIPlugins;

namespace KIPIImgurExportPlugin
{

ImgurWidget::ImgurWidget(KIPI::Interface* interface, QWidget* parent)
    : QWidget(parent)
{

    QHBoxLayout* mainLayout = new QHBoxLayout(this);
    m_imagesList = new ImagesList(interface, this);

//        m_imagesList->addActions();
//        ProgressWidget *p = new ProgressWidget(interface);
//        p->show();

    m_imagesList->loadImagesFromCurrentSelection();
    m_imagesList->setAllowDuplicate(false);
    m_imagesList->setAllowRAW(false);

    QWidget* settingsBox           = new QWidget(this);
    QVBoxLayout* settingsBoxLayout = new QVBoxLayout(settingsBox);

    m_headerLbl = new QLabel(settingsBox);
    m_headerLbl->setWhatsThis(i18n("This is a clickable link to open the Imgur home page in a web browser"));
    m_headerLbl->setText(QString("<b><h2><a href='http://imgur.com'>Imgur</a></h2></b>"));
    m_headerLbl->setOpenExternalLinks(true);
    m_headerLbl->setFocusPolicy(Qt::NoFocus);

    m_progressBar = new QProgressBar(settingsBox);
    m_progressBar->setSizePolicy(QSizePolicy::Preferred ,QSizePolicy::Fixed);
    m_progressBar->setVisible(false);

    // --------------------------------------------

    settingsBoxLayout->addWidget(m_headerLbl);

    settingsBoxLayout->addWidget(m_progressBar);
    settingsBoxLayout->setSpacing(KDialog::spacingHint());
    settingsBoxLayout->setMargin(KDialog::spacingHint());

    // --------------------------------------------

    mainLayout->addWidget(m_imagesList);
    mainLayout->addWidget(settingsBox);
    mainLayout->setSpacing(KDialog::spacingHint());
    mainLayout->setMargin(0);

}

ImgurWidget::~ImgurWidget()
{
    //
}

KIPIPlugins::ImagesList* ImgurWidget::imagesList() const
{
    return m_imagesList;
}

QProgressBar* ImgurWidget::progressBar() const
{
    return m_progressBar;
}

} // namespace KIPIImgurExportPlugin