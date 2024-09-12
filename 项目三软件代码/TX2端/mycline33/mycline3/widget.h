#ifndef WIDGET_H
#define WIDGET_H
#include"serial.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>
#include <QImage>
#include <QByteArray>
#include <QBuffer>
#include <QDebug>
#include <QFile>
#include<QMessageBox>
#include <QFileInfo>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void on_but_open_cam_clicked();

    void on_but_close_cam_clicked();
    void cap_pic();
    void connect_success();
    void transfer_pic();


   // void clintInfoSlot();
   // void clintInfoSlot2();

    void newClinetHandler();
    void newClinetHandler11();
    void transfer_pic1();

    void on_pushButton_3_clicked();

private:
    Ui::Widget *ui;
    QTcpSocket *socket;
   // QCamera *cam;
    QTimer *tim;
    QTimer *tim1;
    QTcpSocket *mycli;
  //  QCameraImageCapture *imgcap;
    QTcpSocket *socket1;
    QTcpServer *server1;
    QTcpSocket *socket2;
    QTcpSocket *socket22;
    QTcpSocket *socket3;
    QTcpServer *server11;
    int i;



};
#endif // WIDGET_H
