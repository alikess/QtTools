#ifndef HTTPPROTOCOL_H
#define HTTPPROTOCOL_H

#include "qjsondocument.h"
#include "qnetworkreply.h"

#include <QEventLoop>
#include <QJsonObject>
#include <QNetworkAccessManager>


class HttpProtocol
{
public:
    HttpProtocol();
    QJsonObject GetRquest(QString url);
    QJsonObject PostRquest(QString url, QJsonObject json);
    QString getCmdResult(const QString &strCmd);
    QJsonObject parseJsonString(const QByteArray &jsonBytes);
};

#endif // HTTPPROTOCOL_H
