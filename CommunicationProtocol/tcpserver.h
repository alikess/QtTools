#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    explicit TcpServer(QObject *parent = nullptr);
    ~TcpServer();
    void ListenAllIp(int port);//监听所有ip
public slots:
    void ClientConnect();//解析新客户连接
    void ReadData();//读取数据
signals:

private:
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;
};

#endif // TCPSERVER_H
