#include "shop.h"
#include "ui_shop.h"

shop::shop(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::shop)
{
    ui->setupUi(this);
}

shop::~shop()
{
    delete ui;
}
