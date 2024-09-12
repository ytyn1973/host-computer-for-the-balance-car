#include "serial.h"
#include "ui_serial.h"


serial::serial(QTcpSocket *s, QTcpSocket *t, QTcpSocket *r, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::serial)
{
    ui->setupUi(this);
    socket1=s;
    socket2=t;
    socket3=r;
    m_serialPort = new QSerialPort();
    m_portNameList = getPortNameList();
    ui->m_PortNameComboBox->addItems(m_portNameList);
    connect(socket1,&QTcpSocket::readyRead,this,&serial::clintInfoSlot2);
    connect(socket2,&QTcpSocket::readyRead,this,&serial::clintInfoSlot2);//socket2为视觉发来的消息
    connect(socket3,&QTcpSocket::readyRead,this,&serial::clintInfoSlot2);//socket3为视觉的消息
}

serial::~serial()
{
    delete ui;
}
QStringList serial::getPortNameList()
{
    QStringList m_serialPortName;
    foreach(const QSerialPortInfo &info,QSerialPortInfo::availablePorts())
    {
        m_serialPortName << info.portName();
        qDebug()<<"serialPortName:"<<info.portName();
    }
    return m_serialPortName;
}


void serial::on_pushButton_clicked()
{
    if(m_serialPort->isOpen())//如果串口已经打开了 先给他关闭了
    {
        m_serialPort->clear();
        m_serialPort->close();
    }


    m_serialPort->setPortName(ui->m_PortNameComboBox->currentText());//当前选择的串口名字
    if(!m_serialPort->open(QIODevice::ReadWrite))//用ReadWrite 的模式尝试打开串口
    {
        qDebug()<<"打开失败!";
        return;
    }
    qDebug()<<"串口打开成功!";

    m_serialPort->setBaudRate(QSerialPort::Baud115200,QSerialPort::AllDirections);//设置波特率和读写方向
    m_serialPort->setDataBits(QSerialPort::Data8);      //数据位为8位
    m_serialPort->setFlowControl(QSerialPort::NoFlowControl);//无流控制
    m_serialPort->setParity(QSerialPort::NoParity); //无校验位
    m_serialPort->setStopBits(QSerialPort::OneStop); //一位停止位

    connect(m_serialPort,SIGNAL(readyRead()),this,SLOT(receiveInfo()));
}
//接收到单片机发送的数据进行解析
void serial::receiveInfo()
{
    QByteArray info = m_serialPort->readAll();
    socket1->write(info);

}

void serial::clintInfoSlot2()
{
   qDebug()<<"121";
  QTcpSocket *s=(QTcpSocket *) sender();//获取信号的发出者
  QByteArray data= s->readAll(); // 从socket1中读取所有数据
  //qDebug() << data; // 打印出data的值
  qDebug()<<data.toHex(' ');//将数组按字节打印。中间用空格隔开。
  m_serialPort->write(data);
}
