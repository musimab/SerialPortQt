#ifndef RECEIVER_H
#define RECEIVER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include <QMessageBox>

class Receiver :public QObject
{
    Q_OBJECT

     QByteArray m_buffer;
     QSerialPort* m_arduino;
     QString parsed_data;
     double temperature_value;
     static const quint16 arduaino_uno_vendor_id = 6790;
     static const quint16 arduaino_uno_product_id = 29987;

     void processLine(const QByteArray& line);
     int get_arduino_product_info();
     void init_serial_port_configurations();


public slots:
     void readSerial();
     void writeSerial(QString command);
signals:
     void sendReceivedData(double temperature);
     public:
    Receiver(QObject* receiver = nullptr);
     double get_temperature_value();
    ~Receiver();
};

#endif // RECEIVER_H
