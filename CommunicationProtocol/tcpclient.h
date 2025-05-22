#ifndef TCPCLIENT_H
#define TCPCLIENT_H

#include <QObject>
#include <QTcpSocket>

class TcpClient : public QObject
{
    Q_OBJECT

public:
    TcpClient();
    QStringList GetLocalIp();//获取本地ip
    void Connect(QString ip,int port);//连接ip+port
    QByteArray ReadData();//读取数据
    void Close();
    bool SendData(QByteArray data);//发送数据
private:
    QTcpSocket *socket = nullptr;
    QString ip;

};

#endif // TCPCLIENT_H
