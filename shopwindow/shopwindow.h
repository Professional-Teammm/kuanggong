#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLabel>
#include<QGridLayout>
#include<QStringList>
#include<QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    Ui::MainWindow *ui;
    QStringList name = {"力量饮料","钟表","合金缆绳","四叶草","宝石上光剂","炸弹"};
    //QList<int> price = {100,200,300,400,500,600};

    //总共积累的金币数目需要传递给商店界面
    int sum_of_money=500;

    //我的想法是用一个bool数组记录6种商品的购买情况
    //这些二维数组记录为真（1）和为假（0）两种情况下参数的值
    bool have[7]={0};
    int new_k[2]={1,3};
    int time_plus[2]={0,20};
    int lift_heavy[2]={0,1};//下一关不一定要出现非常重的物块（概率增加游戏乐趣）
    double gold_in_bag[2]={0.4,0.6};//0.4的概率获得$200的奖励；后者是0.6的概率
    int diamond_value[2]={400,500};//下一关钻石数目未知
    int bomb_increase[2]={0,1};

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //void paintEvent(QPaintEvent* event);
private slots:
    void on_pushButton_clicked();
    void handlepurchasebutton();

    void on_pushButton_2_clicked();
    void handlepurchasebutton2();

    void on_pushButton_3_clicked();
    void handlepurchasebutton3();

    void on_pushButton_4_clicked();
    void handlepurchasebutton4();

    void on_pushButton_5_clicked();
    void handlepurchasebutton5();

    void on_pushButton_6_clicked();
    void handlepurchasebutton6();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_9_clicked();

    void lack_money();
};
#endif // MAINWINDOW_H
