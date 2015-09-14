/* ============================================================
*
* This file is a part of kipi-plugins project
* http://www.digikam.org
*
* Date        : 2012-02-02
* Description : a plugin to export photos or videos to ImageShack web service
*
* Copyright (C) 2012 Dodon Victor <dodonvictor at gmail dot com>
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

#include "imageshacktalker.h"

// Qt includes

#include <QJsonDocument>
#include <QJsonParseError>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>
#include <QMap>
#include <QString>
#include <QDomDocument>
#include <QDomElement>
#include <QDomNode>
#include <QXmlStreamReader>
#include <QApplication>
#include <QtCore/QMimeDatabase>
#include <QtCore/QMimeType>
#include <QUrlQuery>

// KDE includes

#include <kio/job.h>
#include <ktoolinvocation.h>
#include <kio/jobuidelegate.h>

// Local includes

#include "kpversion.h"
#include "imageshack.h"
#include "mpform.h"
#include "kipiplugins_debug.h"

namespace KIPIImageshackPlugin
{

ImageshackTalker::ImageshackTalker(Imageshack* const imghack)
    : m_imageshack(imghack),
      m_loginInProgress(false),
      m_job(0),
      m_state(IMGHCK_DONOTHING)
{
    m_userAgent   = QStringLiteral("KIPI-Plugin-Imageshack/%1").arg(kipipluginsVersion());
    m_photoApiUrl = QUrl(QStringLiteral("https://api.imageshack.com/v2/images"));
    m_videoApiUrl = QUrl(QStringLiteral("http://render.imageshack.us/upload_api.php"));
    m_loginApiUrl = QUrl(QStringLiteral("http://my.imageshack.us/setlogin.php"));
    m_galleryUrl  = QUrl(QStringLiteral("http://www.imageshack.us/gallery_api.php"));
    m_appKey      = QStringLiteral("YPZ2L9WV2de2a1e08e8fbddfbcc1c5c39f94f92a");
}

ImageshackTalker::~ImageshackTalker()
{
    if (m_job)
        m_job->kill();
}

void ImageshackTalker::cancel()
{
    if (m_job)
    {
        m_job->kill();
        m_job = 0;
    }

    emit signalBusy(false);
}

QString ImageshackTalker::getCallString(QMap< QString, QString >& args)
{
    QString result;
    for (QMap<QString, QString>::const_iterator it = args.constBegin();
         it != args.constEnd();
         ++it)
    {
        if (!result.isEmpty())
            result.append(QStringLiteral("&"));
        result.append(it.key());
        result.append(QStringLiteral("="));
        result.append(it.value());
    }

    return result;
}

void ImageshackTalker::data(KIO::Job* /*job*/, const QByteArray& data)
{
    if (data.isEmpty())
        return;

    int oldSize = m_buffer.size();
    m_buffer.resize(m_buffer.size() + data.size());
    memcpy(m_buffer.data()+oldSize, data.data(), data.size());
}

void ImageshackTalker::slotResult(KJob* kjob)
{
    KIO::Job* job = static_cast<KIO::Job*>(kjob);

    if (job->error())
    {
        if (m_state == IMGHCK_AUTHENTICATING)
        {
            checkRegistrationCodeDone(job->error(), job->errorString());
            emit signalBusy(false);
        }
        else if (m_state == IMGHCK_GETGALLERIES)
        {
            emit signalBusy(false);
            emit signalGetGalleriesDone(job->error(), job->errorString());
        }
        else if (m_state == IMGHCK_ADDPHOTO || m_state == IMGHCK_ADDPHOTOGALLERY)
        {
            emit signalBusy(false);
            emit signalAddPhotoDone(job->error(), job->errorString());
        }
        m_state = IMGHCK_DONOTHING;
        m_job = 0;
        return;
    }

    int step;
    switch (m_state)
    {
        case IMGHCK_AUTHENTICATING:
            m_job = 0;
            parseAccessToken(m_buffer);
            break;
        case IMGHCK_ADDPHOTOGALLERY:
            step = job->property("k_step").toInt();
            if (step == STEP_UPLOADITEM)
                parseUploadPhotoDone(m_buffer);
            else
                parseAddPhotoToGalleryDone(m_buffer);
            break;
        case IMGHCK_ADDVIDEO:
        case IMGHCK_ADDPHOTO:
            m_job = 0;
            parseUploadPhotoDone(m_buffer);
            break;
        case IMGHCK_GETGALLERIES:
            m_job = 0;
            parseGetGalleries(m_buffer);
            break;
        default:
            break;
    }
}


void ImageshackTalker::authenticate()
{   
    if (m_job)
    {
        m_job->kill();
        m_job = 0;
    }
    
    emit signalBusy(true);
    emit signalJobInProgress(1, 4, i18n("Authenticating the user"));
    
    QUrl url(QStringLiteral("https://api.imageshack.com/v2/user/login"));
    QUrlQuery q(url);
    q.addQueryItem(QStringLiteral("user"), m_imageshack->email());
    q.addQueryItem(QStringLiteral("password"), m_imageshack->password());
    url.setQuery(q);
    
    KIO::TransferJob* const job = KIO::http_post(url,"",KIO::HideProgressInfo);
    job->addMetaData(QStringLiteral("content-type"),
                     QStringLiteral("Content-Type : application/x-www-form-urlencoded"));
    
    connect(job, SIGNAL(data(KIO::Job*,QByteArray)),
            this, SLOT(data(KIO::Job*,QByteArray)));

    connect(job, SIGNAL(result(KJob*)),
            this, SLOT(slotResult(KJob*)));

    m_state = IMGHCK_AUTHENTICATING;
    m_job = job;
    m_buffer.resize(0);    
}

void ImageshackTalker::getGalleries()
{
    if (m_job)
    {
        m_job->kill();
        m_job = 0;
    }

    emit signalBusy(true);
    emit signalJobInProgress(3, 4, i18n("Getting galleries from server"));

    QUrl gUrl(m_galleryUrl);

    QUrlQuery q(gUrl);
    q.addQueryItem(QStringLiteral("action"), QStringLiteral("gallery_list"));
    q.addQueryItem(QStringLiteral("user"), m_imageshack->username());
    gUrl.setQuery(q);

    KIO::TransferJob* const job = KIO::get(gUrl, KIO::NoReload, KIO::HideProgressInfo);

    connect(job, SIGNAL(data(KIO::Job*,QByteArray)),
            this, SLOT(data(KIO::Job*,QByteArray)));

    connect(job, SIGNAL(result(KJob*)),
            this, SLOT(slotResult(KJob*)));

    m_state = IMGHCK_GETGALLERIES;
    m_job = job;
    m_buffer.resize(0);
}

void ImageshackTalker::checkRegistrationCodeDone(int errCode, const QString& errMsg)
{
    emit signalBusy(false);
    emit signalLoginDone(errCode, errMsg);
    m_loginInProgress = false;
}

void ImageshackTalker::parseAccessToken(const QByteArray &data)
{
    qCDebug(KIPIPLUGINS_LOG) << "Data received is "<< data;  
    
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    
    if(err.error != QJsonParseError::NoError)
    {
        emit signalBusy(false);
        return;
    }
    
    QJsonObject jsonObject = doc.object();
        
    if(jsonObject[QStringLiteral("success")].toBool())    
    {
        m_imageshack->m_loggedIn = true;
        QJsonObject obj = jsonObject[QStringLiteral("result")].toObject();
        m_imageshack->setUsername(obj[QStringLiteral("username")].toString());
        m_imageshack->setEmail(obj[QStringLiteral("email")].toString());
        m_imageshack->setAuthToken(obj[QStringLiteral("auth_token")].toString());
        checkRegistrationCodeDone(0,QStringLiteral(""));
    }
    else
    {
        m_imageshack->m_loggedIn = false;
        QJsonObject obj = jsonObject[QStringLiteral("error")].toObject();
        checkRegistrationCodeDone(obj[QStringLiteral("error_code")].toInt(), obj[QStringLiteral("error_message")].toString());
    }
}

void ImageshackTalker::parseGetGalleries(const QByteArray &data)
{
    QDomDocument document;
    if (!document.setContent(data))
        return;

    QDomElement rootElem  = document.documentElement();
    QDomNodeList children = rootElem.childNodes();

    QStringList gTexts;
    QStringList gNames;

    for (int i = 0; i < children.size(); ++i)
    {
        QDomElement e = children.at(i).toElement();
        if (e.tagName() == QStringLiteral("gallery"))
        {
            QDomElement nameElem   = e.firstChildElement(QStringLiteral("name"));
            QDomElement titleElem  = e.firstChildElement(QStringLiteral("title"));
            QDomElement serverElem = e.firstChildElement(QStringLiteral("server"));

            if (!nameElem.isNull())
            {
                QString fmt;
                fmt          = nameElem.firstChild().toText().data();
                gNames << nameElem.firstChild().toText().data();
                gTexts << titleElem.firstChild().toText().data();
            }
        }
    }

    m_state = IMGHCK_DONOTHING;

    emit signalUpdateGalleries(gTexts, gNames);
    emit signalGetGalleriesDone(0, i18n("Successfully retrieved galleries"));
}

void ImageshackTalker::authenticationDone(int errCode, const QString& errMsg)
{
    if (errCode)
    {
        m_imageshack->logOut();
    }

    emit signalBusy(false);
    emit signalLoginDone(errCode, errMsg);
    m_loginInProgress = false;
}

void ImageshackTalker::logOut()
{
    m_imageshack->logOut();
    m_loginInProgress = false;
}

void ImageshackTalker::cancelLogIn()
{
    logOut();
    emit signalLoginDone(-1, QStringLiteral("Canceled by the user!"));
}

QString ImageshackTalker::mimeType(const QString& path)
{
    QMimeDatabase db;
    QMimeType ptr = db.mimeTypeForUrl(QUrl::fromLocalFile(path));
    return ptr.name();
}

void ImageshackTalker::uploadItem(const QString& path, const QMap<QString, QString>& opts)
{
    
    if (m_job)
    {
        m_job->kill();
        m_job = 0;
    }

    emit signalBusy(true);
    QMap<QString, QString> args;
    args[QStringLiteral("key")]        = m_appKey;
    args[QStringLiteral("fileupload")] = QUrl(path).fileName();

    MPForm form;

    for (QMap<QString, QString>::const_iterator it = opts.constBegin();
         it != opts.constEnd();
         ++it)
    {
        form.addPair(it.key(), it.value());
    }

    for (QMap<QString, QString>::const_iterator it = args.constBegin();
         it != args.constEnd();
         ++it)
    {
        form.addPair(it.key(), it.value());
    }

    if (!form.addFile(QUrl(path).fileName(), path))
    {
        emit signalBusy(false);
        return;
    }

    form.finish();    
    
    QUrl uploadUrl = QUrl(m_photoApiUrl);
    m_state   = IMGHCK_ADDPHOTO;
    
    KIO::Job* const job = KIO::http_post(uploadUrl, form.formData(), KIO::HideProgressInfo);
    job->addMetaData(QStringLiteral("UserAgent"), m_userAgent);
    job->addMetaData(QStringLiteral("content-type"), form.contentType());

    m_job = job;

    connect(job, SIGNAL(data(KIO::Job*,QByteArray)),
            this, SLOT(data(KIO::Job*,QByteArray)));

    connect(job, SIGNAL(result(KJob*)),
            this, SLOT(slotResult(KJob*)));    
    //uploadItemToGallery(path, QStringLiteral(""), opts);
}

void ImageshackTalker::uploadItemToGallery(const QString& path, const QString& /*gallery*/, const QMap<QString, QString>& opts)
{
    if (m_job)
    {
        m_job->kill();
        m_job = 0;
    }

    emit signalBusy(true);
    QMap<QString, QString> args;
    args[QStringLiteral("key")]        = m_appKey;
    args[QStringLiteral("fileupload")] = QUrl(path).fileName();

    MPForm form;

    for (QMap<QString, QString>::const_iterator it = opts.constBegin();
         it != opts.constEnd();
         ++it)
    {
        form.addPair(it.key(), it.value());
    }

    for (QMap<QString, QString>::const_iterator it = args.constBegin();
         it != args.constEnd();
         ++it)
    {
        form.addPair(it.key(), it.value());
    }

    if (!form.addFile(QUrl(path).fileName(), path))
    {
        emit signalBusy(false);
        return;
    }

    form.finish();

    // Check where to upload
    QString mime = mimeType(path);

    QUrl uploadUrl;
    
    uploadUrl = QUrl(m_photoApiUrl);
    m_state   = IMGHCK_ADDPHOTO;

    KIO::Job* const job = KIO::http_post(uploadUrl, form.formData(), KIO::HideProgressInfo);
    job->addMetaData(QStringLiteral("UserAgent"), m_userAgent);
    job->addMetaData(QStringLiteral("content-type"), form.contentType());

    m_job = job;
    
    m_buffer.resize(0);

    connect(job, SIGNAL(data(KIO::Job*,QByteArray)),
            this, SLOT(data(KIO::Job*,QByteArray)));

    connect(job, SIGNAL(result(KJob*)),
            this, SLOT(slotResult(KJob*)));

}

int ImageshackTalker::parseErrorResponse(QDomElement elem, QString& errMsg)
{
    int errCode = -1;
    QString err_code;

    for (QDomNode node = elem.firstChild();
         !node.isNull();
         node = node.nextSibling())
    {
        if (!node.isElement())
            continue;

        QDomElement e = node.toElement();

        if (e.tagName() == QStringLiteral("error"))
        {
            err_code = e.attributeNode(QStringLiteral("id")).value();
            errMsg = e.text();
        }
    }

    if (err_code == QStringLiteral("file_too_big"))
    {
        errCode = 501;
    }
    else
    {
        errCode = 502;
    }

    return errCode;
}

void ImageshackTalker::parseUploadPhotoDone(QByteArray data)
{
    qCDebug(KIPIPLUGINS_LOG) << "ParseUploadPhotoDone data is "<<data;
    
    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(data, &err);
    
    if(err.error != QJsonParseError::NoError)
    {
        emit signalBusy(false);
        return;
    }
    
    QJsonObject jsonObject = doc.object();
    
    if(m_state == IMGHCK_ADDPHOTO || m_state == IMGHCK_ADDVIDEO
            || (m_state == IMGHCK_ADDPHOTOGALLERY))
    {
        if(jsonObject[QStringLiteral("success")].toBool())    
        {
            emit signalBusy(false);
            emit signalAddPhotoDone(0,QStringLiteral(""));
        }
        else
        {
            QJsonObject obj = jsonObject[QStringLiteral("error")].toObject();
            emit signalAddPhotoDone(obj[QStringLiteral("error_code")].toInt(), obj[QStringLiteral("error_message")].toString());
            emit signalBusy(false);
        }        
    }
}

void ImageshackTalker::parseAddPhotoToGalleryDone(QByteArray data)
{
//    int errCode = -1;
    QString errMsg = QStringLiteral("");
    QDomDocument domDoc(QStringLiteral("galleryXML"));

    qCDebug(KIPIPLUGINS_LOG) << data;

    if (!domDoc.setContent(data))
        return;

    QDomElement rootElem = domDoc.documentElement();

    if (rootElem.isNull() || rootElem.tagName() != QStringLiteral("gallery"))
    {
        // TODO error cheking
    }
    else
    {
        emit signalBusy(false);
        emit signalAddPhotoDone(0, QStringLiteral(""));
    }
}

} // namespace KIPIImageshackPlugin
