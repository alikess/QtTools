#ifndef SERIALPORT_H
#define SERIALPORT_H

#include <QSerialPort>
#include <QStringList>
#include <QDebug>

class SerialPort : QSerialPort
{

public:
    SerialPort();
    QStringList GetSerialPortName();//获取串口
    bool InitSerialPort(QString SerialPortName);//初始化串口
    void CloseSerialPort();//关闭串口
    bool SerialPortIsOpen();//串口是否连接
    QString GetSerialPortCurrentName();//获取当前串口
    void WriteData(QByteArray data);//数据发送
public slots:
    void receiveData();//接受并处理数据

private:
    QSerialPort *m_pSerialPort = nullptr;
};

#endif // SERIALPORT_H
