#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QtGui>
#include<QLabel>
#include<QTimer>
#include<QKeyEvent>

#include<item.h>
#include<miner.h>
#include<map.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

private:

    Ui::MainWindow *ui;

    Miner *miner;
    Map *map;
    QLabel *lable[15];//前2个为大金矿，后4个为小金矿,6-9为随机产生的石头（可重复产生）

    QPixmap pix;//钩子
    QImage background,hook;

    int cur_item;
    double rad;//表示1弧度=多少度
    int angle_change;//1：1°  -1：-1°
    double k;//表示倍数（加减速）

    //计时器
    QTimer timer_hook;//钩子旋转伸长缩短刷新（15ms）
    QTimer timer_clock;//倒计时（1s）
    QTimer timer_miner_up_down;//矿工向上、向下交替运动（200ms）
    int interval_hook,interval_miner;//15，200
    int time_left;//剩余时间
    int time;//表示已经进行了多久，每8秒随机产生一次矿石
    int time_up,time_down;//表示加速和减速的倒计时


public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void paintEvent(QPaintEvent *);
    void keyPressEvent(QKeyEvent *);

    void init();//游戏初始化
    int detection();//碰撞检测， 判断是否碰到物体
    //bool detection();
    void do_stop();//暂停
    void resume();//重新开始
    void updatee();


private slots:

    void time_reduce();//倒计时（1s刷新）
    void rotate();//钩子旋转（15ms刷新）
    void miner_up_down();//矿工向上or向下（200s刷新)
    void hook_length();//绳子伸长or缩短操作(15ms刷新)

    void on_toolButton_start_clicked();//（初始界面）“开始”

    void on_toolButton_reset_clicked();//（游戏界面左上角）重开一局

    void on_toolButton_break_clicked();//（游戏界面）“||”暂停游戏

    void on_toolButton_continue_clicked();//（暂停界面）“继续”

    void on_toolButton_restart_clicked();//（结束界面）“重新开始”

    void on_toolButton_exit_clicked();//（结束界面）“退出”

};

#endif // MAINWINDOW_H
