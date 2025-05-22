#include "httpprotocol.h"

HttpProtocol::HttpProtocol() {}

QJsonObject HttpProtocol::GetRquest(QString url)
{
    QNetworkAccessManager *managerGet = new QNetworkAccessManager();
    QNetworkRequest request;
    QNetworkReply* reply;
    QEventLoop eventLoop;
    QByteArray responseData;
    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    reply = managerGet->get(request);
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    if (reply->error() == QNetworkReply::NoError) {
        responseData = reply->readAll();
    } else {
        responseData = "Error: " + reply->errorString().toUtf8();
        qDebug() << "Error occurred:" << responseData;
    }
    reply->deleteLater();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        return {};
    }
    QJsonObject jsonObj = jsonDoc.object();
    return jsonObj;
}

QJsonObject HttpProtocol::PostRquest(QString url, QJsonObject json)
{
    QNetworkAccessManager *managerPost = new QNetworkAccessManager();
    QNetworkRequest request;
    QJsonDocument doc(json);
    QByteArray postData = doc.toJson();

    request.setUrl(QUrl(url));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    // 发送POST请求
    QNetworkReply* reply = managerPost->post(request, postData);
    // 同步等待响应
    QEventLoop eventLoop;
    QObject::connect(reply, &QNetworkReply::finished, &eventLoop, &QEventLoop::quit);
    eventLoop.exec();
    QByteArray responseData;
    if (reply->error() == QNetworkReply::NoError) {
        responseData = reply->readAll();
    } else {
        responseData = "Error: " + reply->errorString().toUtf8();
        qDebug() << "Error occurred:" << responseData;
    }
    reply->deleteLater();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(responseData);
    if (jsonDoc.isNull() || !jsonDoc.isObject()) {
        return {};
    }
    QJsonObject jsonObj = jsonDoc.object();
    return jsonObj;
}

QJsonObject HttpProtocol::parseJsonString(const QByteArray &jsonBytes)
{
    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonBytes, &parseError);
    // 检查解析是否成功
    if (parseError.error != QJsonParseError::NoError) {
        qDebug() << "JSON 解析失败:" << parseError.errorString();
        return QJsonObject();
    }
    // 获取 JSON 对象
    QJsonObject jsonObj = jsonDoc.object();
    // 处理中文字符（如果需要）
    jsonObj["message"] = QString::fromUtf8(jsonObj["message"].toString().toUtf8());
    return jsonObj;
}

QString HttpProtocol::getCmdResult(const QString &strCmd)
{
    char buf[10240] = {0};
    FILE *pf = NULL;

#ifdef Q_OS_LINUX  //支持LINUX
    if( (pf = popen(strCmd.toStdString().c_str(), "r")) == NULL )
    {
        return "";
    }
#else               //支持windows系统
    if( (pf = _popen(strCmd.toStdString().c_str(), "r")) == NULL )
    {
        return "";
    }
#endif

    std::string strResult;
    while(fgets(buf, sizeof buf, pf))
    {
        strResult += buf;
    }

#ifdef Q_OS_LINUX  //支持LINUX
    pclose(pf);
#else              //支持windows系统
    _pclose(pf);
#endif

    unsigned int iSize =  strResult.size();
    if(iSize > 0 && strResult[iSize - 1] == '\n')
    {
        strResult = strResult.substr(0, iSize - 1);
    }

    return QString::fromLocal8Bit(strResult.c_str());
}
