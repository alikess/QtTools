#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
    : QObject{parent}
{
    server = new QTcpServer();
    connect(server,&QTcpServer::newConnection,this,&TcpServer::ClientConnect);
}

TcpServer::~TcpServer()
{
    server->close();
    server->deleteLater();
}

void TcpServer::ListenAllIp(int port)
{
    server->listen(QHostAddress::Any,port);
}

void TcpServer::ClientConnect()
{
    while (server->hasPendingConnections())
    {
        //连接上后通过socket（QTcpSocket对象）获取连接信息
        socket = server->nextPendingConnection();
        QString str = QString("[ip:%1,port:%2]").arg(socket->peerAddress()
            .toString()).arg(socket->peerPort());//监听客户端是否有消息发送
        connect(socket, &QTcpSocket::readyRead, this, &TcpServer::ReadData);
        //qDebug()<<str;
    }
}

void TcpServer::ReadData()
{
    QByteArray buf = socket->readAll();//readAll最多接收65532的数据
    QString str = QString("[ip:%1,port:%2]").arg(socket->peerAddress()
                            .toString()).arg(socket->peerPort());
    qDebug()<<str<<buf;
}
