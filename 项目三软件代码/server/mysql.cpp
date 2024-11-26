#include "mysql.h"
#include "ui_mysql.h"
static int a = -1;

mySql::mySql(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mySql)
{
    ui->setupUi(this);





    db=QSqlDatabase::addDatabase("QODBC");//加载mysql数据库驱动
    db.setDatabaseName("2");
    db.setUserName("root");
    db.setPassword("123456");
    db.setPort(3306);
    if(db.open())
    {
        QMessageBox::information(this," 连接提示","连接成功");
        m=new QSqlTableModel;
        m->setTable("mydatabase");
        ui->tableView->setModel(m);

    }
    else {
        QMessageBox::warning(this,"连接提示","连接失败");
    }
}

mySql::~mySql()
{
    delete ui;
}
void mySql::on_insetpushButton_clicked()
{
    QString id=ui->idLineEdit->text();
    QString address=ui->nameLineEdit->text();
    address.replace("\\", "\\\\");//转义字符， 一个\会消失
    address.remove("\"");//后续字符串会自动补  "数据库里就不存" 了
    //adress.replace("\\", "/");
    QString time =ui->birthLineEdit->text();
    QString sql =QString("insert into abc.mydatabase values(%1,'%2','%3');").arg(id).arg(address).arg(time);
    qDebug() << __FUNCTION__ << __LINE__ << "sql:" << sql;
    QSqlQuery query;
    if (query.exec(sql))

    {
        QMessageBox::information(this,"插入提示","插入成功");
    }
    else
    {
        QMessageBox::information(this,"插入提示","插入失败");

        qDebug() << __FUNCTION__ << __LINE__ << query.lastError();
    }

}
void mySql::on_findpushButton_clicked()
{
    QSqlQuery query;
    query.exec("select * from mydatabase");
    while(query.next())
    {
        qDebug()<<query.value(0);
        qDebug()<<query.value(1);
        qDebug()<<query.value(2);

    }

}
void mySql::on_pushButton_clicked()
{
    m->select();
}

void mySql::on_pushButton_2_clicked()
{
    a++;
    QSqlQuery query;
    query.exec("select * from mydatabase");
    //query.first();
    query.seek(a);
    //for(a=0;a<10;a++){
    QString imagePath = query.value(1).toString();
   //QString imagePath = "C:\\Users\\lmssmdzd\\Desktop\\1.png";
    QPixmap pix(imagePath);
    qDebug() << imagePath;
  //  qDebug() << "\"" << imagePath << "\"";
    ui->imagelabel->setPixmap(pix);
    ui->imagelabel->setScaledContents(true);
   // query.next();
}




void mySql::on_pushButton_3_clicked()
{

        a--;
        QSqlQuery query;
        query.exec("select * from mydatabase");
        //query.first();
        query.seek(a);
        //for(a=0;a<10;a++){
        QString imagePath = query.value(1).toString();
       //QString imagePath = "C:\\Users\\lmssmdzd\\Desktop\\1.png";
        QPixmap pix(imagePath);
        qDebug() << imagePath;
      //  qDebug() << "\"" << imagePath << "\"";
        ui->imagelabel->setPixmap(pix);
        ui->imagelabel->setScaledContents(true);
       // query.next();
    }


void mySql::on_pushButton_4_clicked()
{
    QSqlQuery query;
    query.exec("select * from mydatabase");
    //query.first();
    query.seek(a);
    //for(a=0;a<10;a++){
    QString imagePath = query.value(1).toString();
    QFileInfo FileInfo(imagePath);
    QFile::remove(imagePath);
}
