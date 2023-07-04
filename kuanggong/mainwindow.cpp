#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<math.h>
#include<stdlib.h>
#include<time.h>
#include<QDebug>
#include<QString>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    miner=new Miner;
    map=new Map;
    lable[0]=ui->label_1;lable[1]=ui->label_2;lable[2]=ui->label_3;
    lable[3]=ui->label_4;lable[4]=ui->label_5;lable[5]=ui->label_6;
    lable[6]=ui->label_7;lable[7]=ui->label_8;lable[8]=ui->label_9;
    lable[9]=ui->label_10;lable[10]=ui->label_11;lable[11]=ui->label_12;
    lable[12]=ui->label_13;lable[13]=ui->label_14;
    //lable[i]:0,1,6大金矿  2,3,4,5,7,8小金矿   9钻石 10加速 11减速 12时间 13随机物品

    setFixedSize(700, 600);
    setWindowTitle(tr("黄金矿工"));

    //QPixmap pixmap(":/images/iii/cursor.png");
    QPixmap pixmap(":/newimages/IMG_0397.PNG");
    QCursor cursor= QCursor(pixmap,-1,-1);
    setCursor(cursor);//设置光标图案

    QPalette pal;
    pal.setColor(QPalette::WindowText, Qt::yellow);
    ui->label_final->setPalette(pal);//设置结束界面分数颜色

    this->setStyleSheet("#MainWindow{border-image:url(:/images/iii/background.jpg);}");//设置背景图片
    pix.load("://images//iii//hook.png");//设置钩子图片（60*50）
    //pix.load(":/newimages/newimage/hook.PNG");

    rad=180/3.1415926;//1弧度
    angle_change=1;//角度转变量为1°
    k=1;

    interval_hook=15;
    interval_miner=200;

    timer_hook.setInterval(interval_hook);//设置触发间隔为15ms-->rotate,ss
    connect(&timer_hook,&QTimer::timeout,this,&MainWindow::rotate);
    connect(&timer_hook,&QTimer::timeout,this,&MainWindow::hook_length);

    timer_miner_up_down.setInterval(interval_miner);//s控制矿工的运动--200ms-->miner_up_down
    connect(&timer_miner_up_down,&QTimer::timeout,this,&MainWindow::miner_up_down);

    timer_clock.setInterval(1000);//每1s更新显示倒计时数字减一time_reduce
    connect(&timer_clock,&QTimer::timeout,this,&MainWindow::time_reduce);

    //timer_update.setInterval(5);
    //connect(&timer_update,&QTimer::timeout,this,&MainWindow::updatee);

    init();//以下6行待优化
    do_stop();//暂停，跳出帮助菜单
    ui->label_rule->setVisible(false);//规则图案
    ui->toolButton_continue->setVisible(false);

    ui->label_finish_background->setVisible(false);//结束背景
    ui->toolButton_restart->setVisible(false);
    ui->toolButton_exit->setVisible(false);
    ui->label_final->setVisible(false);

    ui->label_begin_background->setVisible(true);
    ui->toolButton_start->setVisible(true);
}

void MainWindow::updatee(){
    update();
}


void MainWindow::init()//游戏初始化
{
    miner->init();//矿工初始化设置
    map->init();//地图初始化设置

    time_left=60;//剩余时间为60s
    time=time_up=time_down=0;
    ui->lcdNumber_time->display(time_left);
    ui->lcdNumber_sum->display(miner->get_sum());

    for(int i=0;i<=5;++i)
    {
        lable[i]->setVisible(true);//游戏开始时0-5大小矿石可见
        lable[i]->move(map->get_point(i));
        if(i<2){
            lable[i]->resize(140,120);
        }else{
            lable[i]->resize(60,50);
        }
    }
    for(int i=6;i<=13;++i){  //让随机矿石不可见
        lable[i]->setVisible(false);
    }

    ui->toolButton->setStyleSheet("#toolButton{border-image:url(:/images/iii/miner_init.png);}");//设置矿工

    timer_hook.start();
    timer_clock.start();
    timer_miner_up_down.start();
}

void MainWindow::do_stop()
{
    miner->set_is_rotating(false);
    miner->set_stopped(true);
    timer_clock.stop();
    timer_hook.stop();
    timer_miner_up_down.stop();
}

void MainWindow::resume()
{
    miner->set_is_rotating(true);
    miner->set_stopped(false);
    timer_clock.start();
    timer_hook.start();
    timer_miner_up_down.start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete miner;
    delete map;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    painter.translate(350,100); //让图片的中心作为旋转的中心
    painter.rotate(miner->get_angle()); //顺时针旋转90度
    painter.translate(-350,-100); //使原点复原

    int length=miner->get_length();
    if(miner->isrotating()==false||miner->isstopped())
    {
        QPen pen;
        pen.setWidth(6);
        painter.setPen(pen);
        painter.setRenderHint(QPainter::Antialiasing, true);
        painter.drawLine(350,95,350,95+length);
        painter.drawPixmap(320,95+length,pix);//绘图的起点
    }
    else
        painter.drawPixmap(320,95,pix);//绘图的起点
    //update();//优化？
}


void MainWindow::keyPressEvent(QKeyEvent *e)
{
    int key=e->key();
    if (!miner->isstopped()&&key ==Qt::Key_Down) // 按向下方向键时
    {
        if(miner->isrotating())//如果正在旋转
        {
            miner->set_is_rotating(false);  //停止旋转，进行下拉操作
        }
    }
    if(key==Qt::Key_Space)//暂停功能
    {
        if(miner->isstopped()&&time_left>0){
            ui->label_rule->setVisible(false);//暂停图案
            ui->toolButton_continue->setVisible(false);
            resume();
        }
        else
            do_stop();
    }
}

int MainWindow::detection()//碰撞和越界检测    1:越界   2:碰撞
{
    //定义临时变量angle和length
    int angle=miner->get_angle();
    int length=miner->get_length();

    if(fabs(angle)>45){//从左右越界
        if(length>(350/(sin(fabs(angle/rad)))))
            return 1;
    }
    else if(length>(500/(cos(angle/rad))))//从下越界
        return 1;
    if(map->detection(350-length*sin(angle/rad),95+length*cos(angle/rad)))//如果map.碰撞检测返回为真
    {
        miner->set_is_grab(true);
        return 2;
    }
    return 0;
}


void MainWindow::time_reduce()//计时器  k:倍数  1s
{
    if(time_left>=0)
    {
        ++time;--time_left;
        ui->lcdNumber_time->display(time_left);
        if(time_down==0&&time_up==0)
        {
            k=1;
            //timer_miner_up_down.setInterval(interval_miner);
            //timer_hook.setInterval(interval_hook);
        }
        if(time_down)
        {
            --time_down;
        }
        if(time_up)
        {
            --time_up;
        }
        if(time%8==0)//每8秒，随机生成矿石一次
        {
            map->rrand();
            for(int i=6;i<=13;++i)
                if(map->is_visible(i))//如果该物体可见
                {
                    lable[i]->setVisible(true);
                    lable[i]->move(map->get_point(i));
                }
        }
    }
    if(time_left<0)//剩余时间为0，则停止游戏
    {

        /*do_stop();
        ui->label_finish_background->setVisible(true);//终止背景
        ui->toolButton_exit->setVisible(true);
        ui->toolButton_restart->setVisible(true);
        ui->label_final->setVisible(true);//final：得分
        QString s = QString::number(miner->get_sum(), 10);
        ui->label_final->setText(s);*/
    }
    update();
}


void MainWindow::rotate()//控制钩子旋转（15ms刷新)  /interval
{
    if(miner->isrotating())//旋转时
    {
        miner->change_angle(angle_change);
        int angle=miner->get_angle();
        if(angle>=90||angle<=-90)
            angle_change*=-1;
    }
    update();
}

//speed: miner:4   big:-4   small:-2   diamond:-3
void MainWindow::hook_length()//绳子伸长or缩短操作(15ms)   /interval   /k
{
    if(!miner->isrotating())
    {
        if(miner->isgrab())//物体的移动
        {   //miner::rlength为当前位置到返回起点的距离
            miner->change_rlength(k*fabs(miner->get_speed()));//绳和钩子移动
            int rlength=miner->get_rlength();
            int angle=miner->get_angle();
            QPoint p=map->get_point(map->get_cur_item());//获取当前物体的坐标
            QPoint temp(rlength*sin(angle/rad),-rlength*cos(angle/rad));//temp为位移大小
            lable[map->get_cur_item()]->move((p+temp));//物体移动
        }else if(miner->get_speed()>0){
            int result=detection();
            if(result==1){
                miner->set_speed(-1*(miner->get_speed()));
            }else if(result==2){//detection()时已设置miner->isgrab()
                miner->set_speed(map->get_cur_speed());
            }
        }

        /*if(miner->isgrab()||detection())//如果已经抓到物体了或碰撞检测返回为true
        {
            if(miner->isgrab())
                miner->set_speed(map->get_cur_speed());
            else
                miner->set_speed(-1*(miner->get_speed()));//速度相反，往反向拉
        }*/

        miner->change_length(k*miner->get_speed());

        if(miner->get_length()<=0)//如果钩子回到了起点
        {
            if(miner->isgrab())//如果抓到了东西
            {
                map->invisible();//令当前物体不可见  //item类有何用?
                lable[map->get_cur_item()]->setVisible(false);//令当前物体不可见
                miner->change_sum(map->get_cur_price());
                miner->set_rlength(0);//
                miner->set_is_grab(false);

                if(map->get_cur_kind())//如果抓到了特殊物品
                {
                    int kind=map->get_cur_kind();
                    if(kind==1)//加速
                    {
                        time_up=10;
                        time_down=0;//不能叠加，所以把另一个的时间归零//叠加如何实现？
                        //timer_miner_up_down.setInterval(30);//快速上下
                        //timer_hook.setInterval(interval_hook);//慢上下
                        k=3;
                    }else if(kind==2)//减速
                    {
                        time_down=10;
                        time_up=0;//不能叠加，所以把另一个的时间归零
                        //timer_miner_up_down.setInterval(interval_miner*2);//慢上下
                        //timer_hook.setInterval(interval_hook*2);//慢上下
                        k=0.5;
                    }
                    else//时间
                        time_left+=15;
                }
            }
            miner->set_is_rotating(true);
            miner->set_speed(4);
        }
    }
    ui->lcdNumber_sum->display(miner->get_sum());
    update();
}


void MainWindow::miner_up_down()//矿工向上or向下（200ms刷新)
{
    if(!miner->isrotating())
    {
        if(miner->isfflag())//矿工的动作设置
            ui->toolButton->setStyleSheet("#toolButton{border-image:url(:/images/iii/miner_down.png);}");
        else
            ui->toolButton->setStyleSheet("#toolButton{border-image:url(:/images/iii/miner_up.png);}");
    }
    update();
}


void MainWindow::on_toolButton_start_clicked()
{
    ui->label_begin_background->setVisible(false);
    ui->toolButton_start->setVisible(false);
    resume();
}


void MainWindow::on_toolButton_reset_clicked()
{
    init();
}


void MainWindow::on_toolButton_break_clicked()
{
    ui->label_rule->setVisible(true);//暂停图案
    ui->toolButton_continue->setVisible(true);
    do_stop();
}


void MainWindow::on_toolButton_continue_clicked()
{
    ui->label_rule->setVisible(false);//暂停图案
    ui->toolButton_continue->setVisible(false);
    resume();
}


void MainWindow::on_toolButton_restart_clicked()
{
    ui->label_finish_background->setVisible(false);//结束背景
    ui->toolButton_restart->setVisible(false);
    ui->toolButton_exit->setVisible(false);
    ui->label_final->setVisible(false);
    init();
}


void MainWindow::on_toolButton_exit_clicked()
{
    qApp->quit();
}
