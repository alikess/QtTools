#include "serialport.h"

#include <QSerialPortInfo>

SerialPort::SerialPort()
{
    m_pSerialPort = new QSerialPort();
}

QStringList SerialPort::GetSerialPortName()
{
    QStringList strListSerialPortName;
    QList<QSerialPortInfo> listPortInfo = QSerialPortInfo::availablePorts();
    foreach(auto it , listPortInfo){
        strListSerialPortName.append(it.portName());
    }
    return strListSerialPortName;
}

bool SerialPort::InitSerialPort(QString SerialPortName)
{
    if(m_pSerialPort->isOpen()){
        m_pSerialPort->setRequestToSend(true);
        m_pSerialPort->setDataTerminalReady(true);
        return true;
    }

    m_pSerialPort->setPortName(SerialPortName);
    m_pSerialPort->setBaudRate(QSerialPort::Baud19200);           //波特率
    m_pSerialPort->setDataBits(QSerialPort::Data8);               //数据位
    m_pSerialPort->setStopBits(QSerialPort::OneStop);             //停止位
    m_pSerialPort->setParity(QSerialPort::NoParity);              //奇偶校验
    m_pSerialPort->setFlowControl(QSerialPort::NoFlowControl);    //流控制

    bool bRtn = false;
    if(m_pSerialPort->open(QIODevice::ReadWrite)){
        m_pSerialPort->setRequestToSend(true);
        m_pSerialPort->setDataTerminalReady(true);
        //qDebug() << "串口初始化成功";
        bRtn = true;
    }
    return bRtn;
}

void SerialPort::CloseSerialPort()
{
    m_pSerialPort->close();
}

bool SerialPort::SerialPortIsOpen()
{
    return m_pSerialPort->isOpen();
}

QString SerialPort::GetSerialPortCurrentName()
{
    return m_pSerialPort->portName();
}

void SerialPort::WriteData(QByteArray data)
{
    m_pSerialPort->write(data);
}



void SerialPort::receiveData()
{
    QByteArray reBuf = m_pSerialPort->readAll();
    QString ReceiceData = QString(reBuf);
    //数据处理
    qDebug()<<ReceiceData;
}

