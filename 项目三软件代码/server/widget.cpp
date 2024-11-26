#include "widget.h"
#include "ui_widget.h"
#include "sdv.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);



    server1 =new QTcpServer;
    server =new QTcpServer;
    server2 =new QTcpServer;
    socket = new QTcpSocket;
    socket2 = new QTcpSocket;
    socket1 = new QTcpSocket;
    i=1;


    server2->listen(QHostAddress::AnyIPv4,3309);
    server->listen(QHostAddress::AnyIPv4,3389);//首尾帧
    server1->listen(QHostAddress::AnyIPv4,3310);

    connect(server,&QTcpServer::newConnection,this,&Widget::newClientHandler);
    connect(server1,&QTcpServer::newConnection,this,&Widget::newClientHandler1);
    connect(server2,&QTcpServer::newConnection,this,&Widget::newClientHandler2);


}

Widget::~Widget()
{
    delete ui;
}
void Widget::newClientHandler()
{       qDebug() << "xixi";
     socket = server->nextPendingConnection();
     connect(socket, &QTcpSocket::readyRead, this, &Widget::readDate2);//首尾帧
}
void Widget::newClientHandler2()
{     //  qDebug() << "No";
    socket2 = server2->nextPendingConnection();
    connect(socket2, &QTcpSocket::readyRead, this, &Widget::readDate);
}

void Widget::readDate()
{
    //   qDebug() << "Noo";
    // 定义一个变量i，用于记录图片的序号
    static int i = 1;

    // 定义一个缓冲区，用于存储图片数据
    static QByteArray data;

    // 定义一个变量，用于记录图片的大小
    static int size = 0;

    // 使用一个循环来读取所有可用的数据
    while (socket2->bytesAvailable() > 0) {
        // 如果图片的大小为0，说明还没有接收到图片大小信息
        if (size == 0) {
            // 读取一行数据，获取图片大小信息
            QByteArray line = socket2->readLine();
            // 分割字符串，获取图片大小
            QString str = QString::fromUtf8(line);
            QStringList list = str.split("=");
            if (list.size() == 2 && list[0] == "size") {
                size = list[1].toInt();
                // 调整缓冲区的大小
                data.resize(size);
                // 发送响应给发送端，表示已经准备好接收图片数据
                socket2->write("ok");
                socket2->waitForBytesWritten();
            }
        } else {
            // 如果图片的大小不为0，说明已经接收到图片大小信息，可以开始接收图片数据
            // 读取图片数据，直到缓冲区满
            int len = socket2->read(data.data() + data.size() - size, size);
            // 减少剩余的大小
            size -= len;
            // 如果剩余的大小为0，说明图片数据已经接收完毕
            if (size == 0) {
                // 从缓冲区加载图片
                QImage image;
                image.loadFromData(data);
                // 使用QString::number(i)函数将i转换为字符串，并与".jpg"拼接
                QFile file("D:/QTproject/QTF1/" + QString::number(i) + ".jpg");
                file.open(QIODevice::WriteOnly | QIODevice::Truncate);
                file.write(data);
                file.close();
                         QPixmap pic = QPixmap::fromImage(image);
                        // ui->lb->resize(800, 800);
                        ui->lb->setPixmap(pic.scaled(ui->lb->size(),Qt::KeepAspectRatio,Qt::SmoothTransformation));
                // 将i加1，以便下次使用
               // i++;
              //  qDebug() << i;
                // 发送响应给发送端，表示已经接收完毕
                socket2->write("ok");
                socket2->waitForBytesWritten();
            }
        }
    }
}
void Widget::paintEvent(QPaintEvent* event)
{
    QStyleOption opt;
    opt.initFrom(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void Widget::readDate2()
{

    // 定义一个变量i，用于记录图片的序号
    static int i = 0;

    // 定义一个缓冲区，用于存储图片数据
    static QByteArray data;

    // 定义一个变量，用于记录图片的大小
    static int size = 0;

    // 使用一个循环来读取所有可用的数据
    while (socket->bytesAvailable() > 0) {
        // 如果图片的大小为0，说明还没有接收到图片大小信息
        if (size == 0) {
            // 读取一行数据，获取图片大小信息
            QByteArray line = socket->readLine();
            // 分割字符串，获取图片大小
            QString str = QString::fromUtf8(line);
            QStringList list = str.split("=");
            if (list.size() == 2 && list[0] == "size") {
                size = list[1].toInt();
                // 调整缓冲区的大小
                data.resize(size);
                // 发送响应给发送端，表示已经准备好接收图片数据
                socket->write("ok");
                socket->waitForBytesWritten();
            }
        } else {
            // 如果图片的大小不为0，说明已经接收到图片大小信息，可以开始接收图片数据
            // 读取图片数据，直到缓冲区满
            int len = socket->read(data.data() + data.size() - size, size);
            // 减少剩余的大小
            size -= len;
            // 如果剩余的大小为0，说明图片数据已经接收完毕
            if (size == 0) {
                // 从缓冲区加载图片
                QImage image;
                image.loadFromData(data);
                // 使用QString::number(i)函数将i转换为字符串，并与".jpg"拼接
                QFile file("D:/QTproject/QTF2/" + QString::number(i) + ".jpg");
                file.open(QIODevice::WriteOnly | QIODevice::Truncate);
                file.write(data);
                file.close();
                // 将i加1，以便下次使用
                i++;
                qDebug() << i;
                // 发送响应给发送端，表示已经接收完毕
                socket->write("ok");
                socket->waitForBytesWritten();
            }
        }
    }
}


void Widget::on_pushButton_clicked()
{
     mySql *c=new mySql;
     c->show();
}


void Widget::on_pushButton_8_clicked()
{

    QByteArray data;
     data.resize(7);
     data[0] = 0xAA;
     data[1] = 0X01;
     data[2] = 0x11;
     data[3] = 0x00;
     data[4] = 0x00;
     data[5] = 0x00;
     data[6] = 0xDD;

    //QByteArray data = "up";
    socket1->write(data);
//    int bytes = socket1->bytesToWrite(); //get the number of bytes to write
//       if (bytes == 0)
//           qDebug()<<"Message sent successfully";
//       else
//           qDebug()<<"Message failed to send";
}


void Widget::on_pushButton_9_clicked()
{
    qDebug()<<"--------------";

        QByteArray data;
         data.resize(7);
         data[0] = 0xaa;
         data[1] = 0X01;
         data[2] = 0x12;
         data[3] = 0x00;
         data[4] = 0x00;
         data[5] = 0x00;
         data[6] = 0xdd;
        socket1->write(data);

}

void Widget::on_pushButton_10_clicked()
{
    QByteArray data;
     data.resize(7);
     data[0] = 0xAA;
     data[1] = 0x01;
     data[2] = 0x13;
     data[3] = 0x00;
     data[4] = 0x00;
     data[5] = 0x00;
     data[6] = 0xDD;
    socket1->write(data);
}

void Widget::on_pushButton_11_clicked()
{
     QByteArray data;
     data.resize(7);
     data[0] = 0xaa;
     data[1] = 0x01;
     data[2] = 0x14;
     data[3] = 0x00;
     data[4] = 0x00;
     data[5] = 0x00;
     data[6] = 0xdd;
    socket1->write(data);
}

void Widget::readDate1()
{
         qDebug() << "Nkko";
         QTcpSocket *s=(QTcpSocket *) sender();//获取信号的发出者
          QByteArray data = s->readAll(); // 从socket1中读取所有数据
          //qDebug() << data; // 打印出data的值
//         QDataStream ds(data);
//         ds>>SJ;
          unsigned char seventhByte =data[6];
          unsigned char sixthByte =data[5];
          unsigned char fifthBye =data[4];
          unsigned char fourthByte = data[3];
          unsigned char firstByte = data[0];
          unsigned char secondByte = data[1];
          unsigned char thirdByte = data[2];//取出第四位字节
          SJ=0;
          SS=0;
                    if(seventhByte==0xDD){
                    {if(firstByte==0xaa){
                        if(secondByte==0x01){
                        //qDebug()<<"角度2:"<<QByteArray(1, sixthByte).toHex();
                        //qDebug()<<"角度1:"<<QByteArray(1, fifthBye).toHex();
                        QByteArray byte = QByteArray(1, sixthByte);
                        QByteArray byte2 = QByteArray(1, fifthBye);
                        QString hexString = byte.toHex();
                        QString hexString2 = byte2.toHex();
                        bool ok; // 用于检查转换是否成功
                        int a = hexString.toInt(&ok,16); // 将十六进制的字符串转换成十进制的整数并赋值给a
                        if (ok) // 如果转换成功
                        {
                          //qDebug() << "a的值:" << a; // 打印出a的值
//                          SJ = a;
//                          SS=SJ;
//                          qDebug() << SJ;
                        }
                        else // 如果转换失败
                        {
                          qDebug() << "转换失败"; // 打印出错误信息
                        }
                        int b = hexString2.toInt(&ok,16);
                        b=b*255;
                       // qDebug() << "b的值:" << b;
                     //   qDebug() << "a的值:" << a;
                        //qDebug() << "SJ的值:" << SJ;
                        SJ+=a;
                        SJ+=b;
                        if(fourthByte==0x02)
                        {
                            SJ=-SJ;
                        }
                        SJ=SJ/100;
                        SS=SJ;

                        qDebug() << "SS的值:" << SS;


                    }
                 }
              }
           }





}
void Widget::newClientHandler1()
{
    socket1 = server1->nextPendingConnection();
  qDebug() << "No data received";
    connect(socket1, &QTcpSocket::readyRead, this, &Widget::readDate1);
}


void Widget::on_pushButton_6_clicked()
{
    QByteArray data;
     data.resize(7);
     data[0] = 0xaa;
     data[1] = 0X01;
     data[2] = 0x10;
     data[3] = 0x00;
     data[4] = 0x00;
     data[5] = 0x00;
     data[6] = 0xdd;
    socket1->write(data);
}

void Widget::on_pushButton_7_clicked()
{
    QByteArray data;
     data.resize(7);
     data[0] = 0xaa;
     data[1] = 0X01;
     data[2] = 0x15;
     data[3] = 0x00;
     data[4] = 0x00;
     data[5] = 0x00;
     data[6] = 0xdd;
    socket1->write(data);
}




