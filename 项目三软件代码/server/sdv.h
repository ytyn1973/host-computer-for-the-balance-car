#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QChartView>
#include <QSplineSeries>
#include <QScatterSeries>
#include <QDebug>
#include <QValueAxis>
#include <QTimer>
#include <QMainWindow>

/*  必需添加命名空间 */
QT_CHARTS_USE_NAMESPACE
extern int SS;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    /* 接收数据接口 */
    void receivedData(int);

    /* 数据最大个数 */
    int maxSize;

    /* x轴上的最大值 */
    int maxX;
    int t;
    /* y轴上的最大值 */
    int maxY;

    /* y轴 */
    QValueAxis *axisY;

    /* x轴 */
    QValueAxis *axisX;

    /* QList int类型容器 */
    QList<int> data;

    /* QSplineSeries对象（曲线）*/
    QSplineSeries *splineSeries;

    /* QChart图表 */
    QChart *chart;

    /* 图表视图 */
    QChartView *chartView;

    /* 定时器 */
    QTimer *timer;
    QTimer *timer1;

private slots:
    void timerTimeOut();
    void timerTimeOut1();
};
#endif // MAINWINDOW_H
