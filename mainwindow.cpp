#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->lcdNumber->display("------");
    serial_port_receiver = new Receiver(this);
    connect(serial_port_receiver, &Receiver::sendReceivedData, this, &MainWindow::show_temperature);

}

MainWindow::~MainWindow()
{

    delete ui;
}

void MainWindow::show_temperature(double temp)
{
    qDebug() <<"Temp:" << temp;
    ui->textEdit->setText(QString::number(temp));
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
     //connect(this, &QSlider::valueChanged, serial_port_receiver, &Receiver::writeSerial);
    serial_port_receiver->writeSerial(QString("r%1").arg(value));
    ui->label_led->setText(QString::number(value));

}

