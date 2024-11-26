#ifndef MYSQL_H
#define MYSQL_H

#include <QWidget>
#include<QSqlDatabase>
#include<QMessageBox>
#include <QDebug>
#include<QSqlQuery>
#include<QSqlDatabase>
#include <QSqlError>
#include<QSqlTableModel>
#include<QFileInfo>
#include<QFile>

namespace Ui {
class mySql;
}

class mySql : public QWidget
{
    Q_OBJECT

public:
    explicit mySql(QWidget *parent = nullptr);
    ~mySql();
    QSqlTableModel *m;
   private slots:
   void on_insetpushButton_clicked();

    void on_findpushButton_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

private:
    Ui::mySql *ui;
    QSqlDatabase db;
};

#endif // MYSQL_H
