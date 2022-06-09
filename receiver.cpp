#include "receiver.h"


Receiver::Receiver(QObject *parent) : QObject(parent)
{
    m_arduino = new QSerialPort(this);
    init_serial_port_configurations();
    connect(m_arduino, &QIODevice::readyRead, this, &Receiver::readSerial);
}

Receiver::~Receiver()
{
    if(m_arduino->isOpen()) {
        m_arduino->close();
    }
}

int Receiver::get_arduino_product_info()
{
    qDebug() << "Number of ports:" << QSerialPortInfo::availablePorts().length() <<"\n";
    foreach(const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()){
            qDebug() << "Description: " << serialPortInfo.description() << "\n";
            qDebug() << "Has vendor id?: " << serialPortInfo.hasVendorIdentifier() << "\n";
            qDebug() << "Vendor ID: " << serialPortInfo.vendorIdentifier() << "\n";
            qDebug() << "Has product id?: " << serialPortInfo.hasProductIdentifier() << "\n";
            qDebug() << "Product ID: " << serialPortInfo.productIdentifier() << "\n";
    }
    return 0;
}

void Receiver::init_serial_port_configurations()
{
    bool arduino_is_available = false;
    QString arduiono_uno_port_name;

    foreach(const QSerialPortInfo & serialPortInfo, QSerialPortInfo::availablePorts()) {
        if(serialPortInfo.hasProductIdentifier() && serialPortInfo.hasVendorIdentifier()) {
            if((serialPortInfo.productIdentifier() == arduaino_uno_product_id)
                    && (serialPortInfo.vendorIdentifier() == arduaino_uno_vendor_id)) {
                arduino_is_available = true;
                arduiono_uno_port_name = serialPortInfo.portName();
            }
        }
    }
    if (arduino_is_available) {
        qDebug() << "Found the arduino port ...\n";
        m_arduino->setPortName(arduiono_uno_port_name);
        m_arduino->open(QSerialPort::ReadOnly);
        m_arduino->setBaudRate(QSerialPort::Baud9600);
        m_arduino->setDataBits(QSerialPort::Data8);
        m_arduino->setFlowControl(QSerialPort::NoFlowControl);
        m_arduino->setParity(QSerialPort::NoParity);
        m_arduino->setStopBits(QSerialPort::OneStop);

     }
    else {
        qDebug() << "Couldnt find the correct port for arduino";
    }
}

double Receiver::get_temperature_value()
{
    return temperature_value;
}

void Receiver::readSerial()
{
    while(m_arduino->canReadLine()) {

        m_buffer = m_arduino->readLine();
        temperature_value = m_buffer.trimmed().toDouble();
        qDebug() << "temperature data:" << temperature_value;
    }

    emit sendReceivedData(temperature_value);



}
