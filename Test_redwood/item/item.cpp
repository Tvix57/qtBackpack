#include "item.h"
#include "ui_item.h"

Item::Item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Item)
{
    ui->setupUi(this);
}

Item::~Item() { delete ui;}
