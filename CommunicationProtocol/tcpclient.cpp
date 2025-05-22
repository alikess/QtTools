#include "tcpclient.h"

#include <QNetworkAddressEntry>

TcpClient::TcpClient() {

    socket = new QTcpSocket();

}

QStringList TcpClient::GetLocalIp()
{
    QStringList ips;
    if (ips.count() == 0) {
#ifdef Q_OS_WASM
        ips << "127.0.0.1";
#else
        QList<QNetworkInterface> netInterfaces = QNetworkInterface::allInterfaces();
        foreach (QNetworkInterface netInterface, netInterfaces) {
            //移除虚拟机和抓包工具的虚拟网卡
            QString humanReadableName = netInterface.humanReadableName().toLower();
            if (humanReadableName.startsWith("vmware network adapter") || humanReadableName.startsWith("npcap loopback adapter")) {
                continue;
            }

            //过滤当前网络接口
            bool flag = (netInterface.flags() == (QNetworkInterface::IsUp | QNetworkInterface::IsRunning | QNetworkInterface::CanBroadcast | QNetworkInterface::CanMulticast));
            if (!flag) {
                continue;
            }

            QList<QNetworkAddressEntry> addrs = netInterface.addressEntries();
            foreach (QNetworkAddressEntry addr, addrs) {
                //只取出IPV4的地址
                if (addr.ip().protocol() != QAbstractSocket::IPv4Protocol) {
                    continue;
                }

                QString ip4 = addr.ip().toString();
                if (ip4 != "127.0.0.1") {
                    ips << ip4;
                }
            }
        }
#endif
    }
    return ips;
}

void TcpClient::Connect(QString ip, int port)
{
    socket->connectToHost(ip,port);
}

bool TcpClient::SendData(QByteArray data)
{
    socket->write(data);
    bool iswrite = socket->waitForBytesWritten();
    return iswrite;
}

QByteArray TcpClient::ReadData()
{
    return socket->readAll();
}

void TcpClient::Close()
{
    socket->disconnectFromHost();
}
