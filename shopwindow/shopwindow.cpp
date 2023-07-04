#include "shopwindow.h"
#include "ui_shopwindow.h"
#include<QPainter>
#include<QPaintEvent>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("GameStore");
    this->setFixedSize(700,600);

    QPalette pa(this->palette());

    /*QImage *imageA = new QImage(":/shop_image/background.png");
    QImage *imageB = new QIamge(":/shop_image/shelf.png");*/

    /*QPainter imagepainter(imageA);
    imagepainter.setCompositionMode(QPainter::CompositionMode_SourceOver);
    imagepainter.drawImage(0,0,*imageB);
    imagepainter.end();*/

    QPixmap Images(":/shop_image/background.jpeg");
    Images=Images.scaled(this->size());

    /*QLabel* shelf = new QLabel(this);
    QPixmap shelf_picture(":/shop_image/shelf.png");
    shelf->setPixmap(shelf_picture.scaled(QSize(600,600)));
    shelf->setAlignment(Qt::AlignHCenter);
    shelf->setGeometry(100,50,500,500);
    QPixmap pi(":/shop_image/shelf.jpeg");
    QLabel* shelfLabel = new QLabel(this);
    shelfLabel->setPixmap(pi);*/

    QBrush *pic = new QBrush(Images);

    pa.setBrush(QPalette::Window,*pic);

    this->setAutoFillBackground(true);
    this->setPalette(pa);

    QString moneystring = "$" + QString::number(sum_of_money);
    ui->label_9->setText(moneystring);

    /*QGridLayout* layout = new QGridLayout();

    QStringList imagePaths = {":/shop_image/energy_drink.png",":/shop_image/clock.png",":/shop_image/rope.png",
                              ":/shop_image/clover.png",":/shop_image/polish.png",":/shop_image/bomb.png"};


    for(int i=0;i<name.size();++i){
        QVBoxLayout* itemLayout = new QVBoxLayout;
        QLabel* imageLabel = new QLabel(this);
        //QLabel* textLabel = new QLabel(this);
        QPixmap pixmap(imagePaths.at(i));
        imageLabel->setPixmap(pixmap);
        imageLabel->setFixedSize(110,120);
        imageLabel->setScaledContents(true);
        //textLabel->setText(name.at(i)+"-"+QString::number(price.at(i)));
        //textLabel->setAlignment(Qt::AlignCenter);
        itemLayout->addWidget(imageLabel);
        //itemLayout->addWidget(textLabel);
        itemLayout->setAlignment(Qt::AlignCenter);
        layout->addLayout(itemLayout,i/3,i%3);
        layout->setAlignment(Qt::AlignCenter);
        layout->setContentsMargins(10,10,40,50);
    }*/
    /*for(int i=0;i<name.size();++i){
        good[i] = new QLabel(this);
        good[i]->setText(name.at(i)+"-"+QString::number(price.at(i)));
        layout->addWidget(good[i],i/3,i%3);
    }

    for(int i=0;i<imagePaths.size();++i){
        QLabel* imageLabel = new QLabel(this);
        QPixmap pixmap(imagePaths.at(i));
        pixmap = pixmap.scaledToWidth(200);
        imageLabel->setPixmap(pixmap);
        layout->addWidget(imageLabel);
    }*/

    /*QWidget* centralWidget = new QWidget(this);
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);*/
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::lack_money(){
    QMessageBox msgbox;
    msgbox.setText("对不起～努力赚更多金币吧");
    msgbox.exec();
}

void MainWindow::on_pushButton_clicked()
{
    QWidget *new_win = new QWidget();
    new_win->resize(200,200);
    new_win->setWindowTitle("力量饮料");

    QPixmap bk(":/shop_image/background.jpeg");
    bk.scaled(new_win->size());
    QPalette palette;
    palette.setBrush(new_win->backgroundRole(),QBrush(bk));
    new_win->setPalette(palette);
    new_win->setAutoFillBackground(true);

    QLabel* label=new QLabel("可以加快下一关中矿工提升的速度\n一次性使用，购买即生效。");
    QPushButton* button=new QPushButton(new_win);
    button->setText("确定购买");
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(button);
    new_win->setLayout(layout);
    new_win->show();
    QObject::connect(button, &QPushButton::clicked, this, [new_win,this](){
        new_win->close();
        if(sum_of_money>=100){
            handlepurchasebutton();
            MainWindow::ui->label->setVisible(false);
            MainWindow::ui->pushButton->setVisible(false);
        }
        else{
            lack_money();
        }
    });
}

void MainWindow::handlepurchasebutton(){
    QMessageBox msgBox;
    sum_of_money-=100;
    QString moneystring="$"+QString::number(sum_of_money);
    ui->label_9->setText(moneystring);
    msgBox.setText("购买成功～");

    /*msgBox.setIcon(QMessageBox::NoIcon);
    msgBox.setStyleSheet("QMessageBox { background-image: url(:/shop_image/background.jpeg); }");*/

    msgBox.exec();
}


void MainWindow::on_pushButton_2_clicked()
{
    QWidget *new_win = new QWidget();
    new_win->resize(200,200);
    new_win->setWindowTitle("时钟");

    QPixmap bk(":/shop_image/background.jpeg");
    bk.scaled(new_win->size());
    QPalette palette;
    palette.setBrush(new_win->backgroundRole(),QBrush(bk));
    new_win->setPalette(palette);
    new_win->setAutoFillBackground(true);

    QLabel* label=new QLabel("可以延长下一关的时间限制\n一次性使用，购买即生效。");
    QPushButton* button=new QPushButton(new_win);
    button->setText("确定购买");
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(button);
    new_win->setLayout(layout);
    new_win->show();
    QObject::connect(button, &QPushButton::clicked, this, [new_win,this](){
        new_win->close();
        if(sum_of_money>=200){
            handlepurchasebutton2();
            MainWindow::ui->label_2->setVisible(false);
            MainWindow::ui->pushButton_2->setVisible(false);
        }
        else{
            lack_money();
        }
    });
}

void MainWindow::handlepurchasebutton2(){
    QMessageBox msgBox;
    sum_of_money-=200;
    QString moneystring="$"+QString::number(sum_of_money);
    ui->label_9->setText(moneystring);
    msgBox.setText("购买成功～");
    msgBox.exec();
}



void MainWindow::on_pushButton_3_clicked()
{
    QWidget *new_win = new QWidget();
    new_win->resize(200,200);
    new_win->setWindowTitle("合金缆绳");

    QPixmap bk(":/shop_image/background.jpeg");
    bk.scaled(new_win->size());
    QPalette palette;
    palette.setBrush(new_win->backgroundRole(),QBrush(bk));
    new_win->setPalette(palette);
    new_win->setAutoFillBackground(true);

    QLabel* label=new QLabel("在下一关中能够提升更重的物品\n一次性使用，购买即生效。");
    QPushButton* button=new QPushButton(new_win);
    button->setText("确定购买");
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(button);
    new_win->setLayout(layout);
    new_win->show();
    QObject::connect(button, &QPushButton::clicked, this, [new_win,this](){
        new_win->close();
        if(sum_of_money>=150){
            handlepurchasebutton3();
            MainWindow::ui->label_3->setVisible(false);
            MainWindow::ui->pushButton_3->setVisible(false);
        }
        else{
            lack_money();
        }
    });
}

void MainWindow::handlepurchasebutton3(){
    QMessageBox msgBox;
    sum_of_money-=150;
    QString moneystring="$"+QString::number(sum_of_money);
    ui->label_9->setText(moneystring);
    msgBox.setText("购买成功～");
    msgBox.exec();
}

void MainWindow::on_pushButton_4_clicked()
{
    QWidget *new_win = new QWidget();
    new_win->resize(200,200);
    new_win->setWindowTitle("三叶草");

    QPixmap bk(":/shop_image/background.jpeg");
    bk.scaled(new_win->size());
    QPalette palette;
    palette.setBrush(new_win->backgroundRole(),QBrush(bk));
    new_win->setPalette(palette);
    new_win->setAutoFillBackground(true);

    QLabel* label=new QLabel("在下一关中有更高概率从神秘袋子里获得更高价值奖励\n一次性使用，购买即生效。");
    QPushButton* button=new QPushButton(new_win);
    button->setText("确定购买");
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(button);
    new_win->setLayout(layout);
    new_win->show();
    QObject::connect(button, &QPushButton::clicked, this, [new_win,this](){
        new_win->close();
        if(sum_of_money>=100){
            handlepurchasebutton4();
            MainWindow::ui->label_4->setVisible(false);
            MainWindow::ui->pushButton_4->setVisible(false);
        }
        else{
            lack_money();
        }
    });
}

void MainWindow::handlepurchasebutton4(){
    QMessageBox msgBox;
    sum_of_money-=100;
    QString moneystring="$"+QString::number(sum_of_money);
    ui->label_9->setText(moneystring);
    msgBox.setText("购买成功～");
    msgBox.exec();
}

void MainWindow::on_pushButton_5_clicked()
{
    QWidget *new_win = new QWidget();
    new_win->resize(200,200);
    new_win->setWindowTitle("宝石上光剂");

    QPixmap bk(":/shop_image/background.jpeg");
    bk.scaled(new_win->size());
    QPalette palette;
    palette.setBrush(new_win->backgroundRole(),QBrush(bk));
    new_win->setPalette(palette);
    new_win->setAutoFillBackground(true);

    QLabel* label=new QLabel("在下一关中钻石的价值更高\n一次性使用，购买即生效。");
    QPushButton* button=new QPushButton(new_win);
    button->setText("确定购买");
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(button);
    new_win->setLayout(layout);
    new_win->show();
    QObject::connect(button, &QPushButton::clicked, this, [new_win,this](){
        new_win->close();
        if(sum_of_money>=250){
            handlepurchasebutton5();
            MainWindow::ui->label_5->setVisible(false);
            MainWindow::ui->pushButton_5->setVisible(false);
        }
        else{
            lack_money();
        }
    });
}

void MainWindow::handlepurchasebutton5(){
    QMessageBox msgBox;
    sum_of_money-=250;
    QString moneystring="$"+QString::number(sum_of_money);
    ui->label_9->setText(moneystring);
    msgBox.setText("购买成功～");
    msgBox.exec();
}

void MainWindow::on_pushButton_6_clicked()
{
    QWidget *new_win = new QWidget();
    new_win->resize(200,200);
    new_win->setWindowTitle("炸药");

    QPixmap bk(":/shop_image/background.jpeg");
    bk.scaled(new_win->size());
    QPalette palette;
    palette.setBrush(new_win->backgroundRole(),QBrush(bk));
    new_win->setPalette(palette);
    new_win->setAutoFillBackground(true);

    QLabel* label=new QLabel("炸掉钩子上的物品\n一次性使用，但可以存储。");//使用炸药应该判断是否有物品
    QPushButton* button=new QPushButton(new_win);
    button->setText("确定购买");
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(label);
    layout->addWidget(button);
    new_win->setLayout(layout);
    new_win->show();
    QObject::connect(button, &QPushButton::clicked, this, [new_win,this](){
        new_win->close();
        if(sum_of_money>=50){
            handlepurchasebutton6();
            MainWindow::ui->label_6->setVisible(false);
            MainWindow::ui->pushButton_6->setVisible(false);
        }
        else{
            lack_money();
        }
    });
}

void MainWindow::handlepurchasebutton6(){
    QMessageBox msgBox;
    sum_of_money-=50;
    QString moneystring="$"+QString::number(sum_of_money);
    ui->label_9->setText(moneystring);
    msgBox.setText("购买成功～");
    msgBox.exec();
}

//这是continue按钮
void MainWindow::on_pushButton_7_clicked()
{

}

//这是exit按钮
void MainWindow::on_pushButton_8_clicked()
{
    qApp->quit();
}


void MainWindow::on_pushButton_9_clicked()
{
    QWidget *new_win = new QWidget();
    new_win->resize(200,200);
    new_win->setWindowTitle("说明");

    QPixmap bk(":/shop_image/background.jpeg");
    bk.scaled(new_win->size());
    QPalette palette;
    palette.setBrush(new_win->backgroundRole(),QBrush(bk));
    new_win->setPalette(palette);
    new_win->setAutoFillBackground(true);

    QLabel* label=new QLabel("点击商品的价格标签\n会弹出对应商品的说明和确认购买的按钮\n注意每件商品每一回合只能购买一次");
    QVBoxLayout* layout=new QVBoxLayout();
    layout->addWidget(label);
    new_win->setLayout(layout);
    new_win->show();
}

