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

#include "plugin_reverseimagesearch.h"

// Qt includes

#include <QMap>
#include <QAction>
#include <QApplication>
#include <QDesktopServices>

// KDE includes

#include <kactioncollection.h>
#include <klocalizedstring.h>
#include <kpluginfactory.h>
#include <kwindowsystem.h>

// Libkipi includes

#include <KIPI/Interface>
#include <KIPI/ImageCollection>

// Local includes

#include "kipiplugins_debug.h"
#include "reverseimagesearchengine.h"

namespace KIPIReverseImageSearchPlugin
{

K_PLUGIN_FACTORY( ReverseImageSearchFactory, registerPlugin<Plugin_ReverseImageSearch>(); )

class Plugin_ReverseImageSearch::Private
{
public:

    Private(){}
    ~Private()
    {
        for(QTemporaryFile* file : files)
        {
            delete file;
        }
    }

    QList<ReverseImageSearchEngine*> engines;
    QList<QAction*> actions;
    QList<QTemporaryFile*> files;
};

Plugin_ReverseImageSearch::Plugin_ReverseImageSearch(QObject* const parent, const QVariantList& args)
    : Plugin(parent, "ReverseImageSearch"),
      d(new Private)
{
    Q_UNUSED(args);

    qCDebug(KIPIPLUGINS_LOG) << "ReverseImageSearch plugin loaded";

    setUiBaseName("kipiplugin_reverseimagesearchui.rc");
    setupXML();
}

Plugin_ReverseImageSearch::~Plugin_ReverseImageSearch()
{
    delete d;
}

void Plugin_ReverseImageSearch::setup(QWidget* const widget)
{
    Plugin::setup(widget);

    if (interface())
    {
        setupActions();
    }
    else
    {
        qCCritical(KIPIPLUGINS_LOG) << "Kipi interface is null!";
    }
}

void Plugin_ReverseImageSearch::setupActions()
{
    setDefaultCategory(ToolsPlugin);

    QMap<QString, QString> enginesToLabels;
    enginesToLabels[QLatin1String("ascii2d")] = i18n("&ASCII2d");
    enginesToLabels[QLatin1String("baidu")] = i18n("&Baidu");
    enginesToLabels[QLatin1String("deepfeatures")] = i18n("&DeepFeatures");
    enginesToLabels[QLatin1String("google")] = i18n("&Google");
    enginesToLabels[QLatin1String("imgops")] = i18n("&ImageOps");
    enginesToLabels[QLatin1String("iqdb")] = i18n("&IQDB");
    enginesToLabels[QLatin1String("3diqdb")] = i18n("&3D IQDB");
    enginesToLabels[QLatin1String("karmadecay")] = i18n("&KarmaDecay");
    enginesToLabels[QLatin1String("saucenao")] = i18n("&SauceNAO");
    enginesToLabels[QLatin1String("tineye")] = i18n("&TinEye");
    enginesToLabels[QLatin1String("viral")] = i18n("&Viral");
    enginesToLabels[QLatin1String("harrylu")] = i18n("&Harry.lu");

    for (auto name : enginesToLabels.keys())
    {
        ReverseImageSearchEngine * engine = new ReverseImageSearchEngine(name, this);

        connect(engine, &ReverseImageSearchEngine::ready,
                this, &Plugin_ReverseImageSearch::openInDefaulWebBrowser);

        d->engines.append(engine);

        QAction * action = new QAction(this);
        action->setText(enginesToLabels.value(name));
        action->setIcon(QIcon::fromTheme(QString::fromLatin1("kipi-reverseimagesearch-%1").arg(name)));

        connect(action, &QAction::triggered, [this, engine](){
            ImageCollection collection = interface()->currentSelection();
            for(auto url : collection.images())
            {
                if (url.isLocalFile())
                {
                    engine->find(url.toLocalFile());
                }
                else
                {
                    qCDebug(KIPIPLUGINS_LOG) << "URL doesn't contain a local file path";
                }
            }
        });

        addAction(name, action);

        d->actions.append(action);
    }
}

void Plugin_ReverseImageSearch::openInDefaulWebBrowser(QTemporaryFile* file)
{
    d->files.append(file);
    QDesktopServices::openUrl(QUrl::fromLocalFile(file->fileName()));
}

} // namespace KIPIReverseImageSearchPlugin

#include "plugin_reverseimagesearch.moc"
