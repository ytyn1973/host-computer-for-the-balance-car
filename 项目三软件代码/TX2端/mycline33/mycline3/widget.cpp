#include "widget.h"
#include "ui_widget.h"


Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    socket = new QTcpSocket;
    server1=new QTcpServer;
    server11=new QTcpServer;
    socket1 = new QTcpSocket;
    socket2 = new QTcpSocket;
    socket22 = new QTcpSocket;
    socket3 = new QTcpSocket;
    i=1;
    server11->listen(QHostAddress::AnyIPv4,8008);
    server1->listen(QHostAddress::AnyIPv4,8001);
   // this->cam=new QCamera(QCameraInfo::defaultCamera());
   // this->cam->setViewfinder(ui->vf);
    this->tim=new QTimer();
    this->tim1=new QTimer();
    //this->imgcap=new QCameraImageCapture(this->cam);
    socket1->connectToHost("192.168.1.101", 3310);//控制姿态的socket连接
    socket3->connectToHost("192.168.1.102", 3319);//传首尾帧
    //被发起连接则发起信号
    connect(server1,&QTcpServer::newConnection,this,&Widget::newClinetHandler);
    connect(server11,&QTcpServer::newConnection,this,&Widget::newClinetHandler11);
    connect(socket3,&QTcpSocket::connected,[this]()
    {
        QMessageBox::information(this," 连接提示","连接服务器成功");
        connect_success();
    })  ;


}

Widget::~Widget()
{
    delete ui;
}


void Widget::on_pushButton_clicked()
{
    //获取IP和端口
    QString IP =ui->ipLineEdit->text();
    QString port =ui->portLineEdit->text();
    socket->connectToHost(QHostAddress(IP),port.toShort());
    //连接服务器
    connect(socket,&QTcpSocket::connected,[this]()
    {
        QMessageBox::information(this," 连接提示","连接服务器成功");
        connect_success();
    })  ;
    // 断开也会发出信号
    connect(socket,&QTcpSocket::disconnected,[this]()
    {
        QMessageBox::warning(this,"连接提示","连接异常 网络断开");
    });
}

void Widget::on_but_open_cam_clicked()
{
  //  this->cam->start();
}

void Widget::on_but_close_cam_clicked()
{
    this->tim->stop();
   // this->cam->stop();
}
void Widget::cap_pic()
{   //qDebug()<<"111";
   // this->imgcap->capture("D:/QTproject/QTF2/1");
}

void Widget::transfer_pic()
{   qDebug()<<"111";
    QImage img("/home/hdgf/Desktop/folder1231.jpg");
    //  img.save("/home/hdgf/Desktop/folder10.jpg","jpg",20);
    QFile file("/home/hdgf/Desktop/folder1231.jpg");
    file.open(QIODevice::ReadOnly);
    QByteArray tem = file.readAll();
    file.close();
    // 获取图片文件的大小
    int size = file.size();
    // 将图片大小转换为字符串，例如"size=123456"
    QString str = QString("size=%1").arg(size);
    // 发送图片大小信息给接收端
    socket->write(str.toUtf8());
    socket->write("\n");
    socket->waitForReadyRead(); // 等待接收端的响应
    // 发送图片数据给接收端
    socket->write(tem);
    socket->waitForReadyRead(); // 等待接收端的响应
}
void Widget::transfer_pic1()
{
    // 定义一个文件路径
    QString path = "/home/hdgf/Desktop/" + QString::number(i) + ".jpg";
    // 创建一个QFileInfo对象
    QFileInfo check_file(path);
    // 检查文件是否存在，如果存在，就继续执行
    if (check_file.exists() && check_file.isFile())
    {
        // 复制文件到一个临时文件
        QFile::copy(path, "/tmp/temp.jpg");
        // 打开临时文件
        QFile file("/tmp/temp.jpg");
        file.open(QIODevice::ReadOnly);
        QByteArray tem = file.readAll();
        file.close();
        // 删除临时文件
        QFile::remove("/tmp/temp.jpg");
        // 获取图片文件的大小
        int size = tem.size();
        // 将图片大小转换为字符串，例如"size=123456"
        QString str = QString("size=%1").arg(size);
        // 发送图片大小信息给接收端
        socket3->write(str.toUtf8());
        socket3->write("\n");
        socket3->waitForReadyRead(); // 等待接收端的响应
        // 发送图片数据给接收端
        socket3->write(tem);
        socket3->waitForReadyRead(); // 等待接收端的响应
        i++;

        // 定义一个固定的图片文件路径
        QString fixed_path = "/home/hdgf/Desktop/a.jpg";
        // 创建一个QFileInfo对象
        QFileInfo check_fixed_file(fixed_path);
        // 检查固定的图片文件是否存在，如果存在，就继续执行
        if (check_fixed_file.exists() && check_fixed_file.isFile())
        {
            // 复制固定的图片文件到一个临时文件
            QFile::copy(fixed_path, "/tmp/temp.jpg");
            // 打开临时文件
            QFile file("/tmp/temp.jpg");
            file.open(QIODevice::ReadOnly);
            QByteArray tem = file.readAll();
            file.close();
            // 删除临时文件
            QFile::remove("/tmp/temp.jpg");
            // 获取固定的图片文件的大小
            int size = tem.size();
            // 将图片大小转换为字符串，例如"size=123456"
            QString str = QString("size=%1").arg(size);
            // 发送图片大小信息给接收端
            socket3->write(str.toUtf8());
            socket3->write("\n");
            socket3->waitForReadyRead(); // 等待接收端的响应
            // 发送图片数据给接收端
            socket3->write(tem);
            socket3->waitForReadyRead(); // 等待接收端的响应
        }
    }
}


void Widget::connect_success()
{
    //连接成功后，启动定时器
    this->tim->start(300);
    this->tim1->start(3000);
    //每隔50ms，调用cap_pic();和transfer_pic();函数
    connect(this->tim,&QTimer::timeout,[this]()
    {   qDebug()<<"--------------";
      //  cap_pic();
        transfer_pic();
    });

    connect(this->tim1,&QTimer::timeout,[this]()
    {   qDebug()<<"--------------";
      //  cap_pic();
        transfer_pic1();
    });
}
void Widget::on_pushButton_3_clicked()
{
    serial *c=new serial(socket1,socket2,socket22);
    c->show();
}
void Widget::newClinetHandler()
{
    socket2 =server1->nextPendingConnection();
    qDebug()<<"新的行人检测连接";

}
void Widget::newClinetHandler11()
{
    socket22 =server11->nextPendingConnection();
    qDebug()<<"新的循连接";

}
