#include "item.h"
#include "ui_item.h"

Item::Item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Item),
    type{Apple}
{
    ui->setupUi(this);
//    :/res/apple_icon.png
    QString test = image_dir_.fileName();
    QPicture img;
    img.load(image_dir_.absoluteFilePath());
    ui->img_lbl->setPicture(img);
}

Item::~Item() { delete ui;}
