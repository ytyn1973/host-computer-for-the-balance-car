#ifndef SERIAL_H
#define SERIAL_H

#include <QWidget>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QComboBox>
#include <QPushButton>
#include<QTcpSocket>
#include <QTcpServer>
#include <QDebug>

namespace Ui {
class serial;
}

class serial : public QWidget
{
    Q_OBJECT

public:
    explicit serial(QTcpSocket *s,QTcpSocket *t,QTcpSocket *r,QWidget *parent = nullptr);
    ~serial();
    QStringList getPortNameList();//获取所有可用的串口列表
public slots:
    void receiveInfo();
private slots:
    void on_pushButton_clicked();
   // void clintInfoSlot();
    void clintInfoSlot2();
private:

        Ui::serial *ui;
        QTcpSocket *socket1;
        QTcpSocket *socket2;
        QTcpSocket *socket3;
        QSerialPort* m_serialPort; //串口类
            QStringList m_portNameList;



};

#endif // SERIAL_H
