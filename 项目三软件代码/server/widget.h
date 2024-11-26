#ifndef WIDGET_H
#define WIDGET_H


#include<QTcpServer>
#include<QString>
#include <QWidget>
#include <QLabel>
#include <QTcpSocket>
#include <QHBoxLayout>
#include <QImage>
#include <QByteArray>
#include <QPixmap>
#include <QDebug>
#include <QFile>
#include "mysql.h"
#include <QStyleOption>



QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    int SJ;
    Widget(QWidget *parent = nullptr);
    ~Widget();
public slots:
    void newClientHandler();
    void newClientHandler2();
    void readDate();
    void readDate1();
    void readDate2();//行人检测
    void paintEvent(QPaintEvent* event);
private slots:

    void on_pushButton_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void newClientHandler1();


    void on_lb_linkActivated(const QString &link);

private:
    Ui::Widget *ui;
    QTcpServer *server;
    QTcpSocket *socket;//接受视频流
    QTcpServer *server1;
    QTcpSocket *socket1;
    QTcpServer *server2;//接受首尾帧
    QTcpSocket *socket2;
    int i;
};
#endif // WIDGET_H
