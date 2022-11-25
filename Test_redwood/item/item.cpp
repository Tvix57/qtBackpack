#include "item.h"

Item::Item(QWidget *parent) :
    QWidget(parent),
    type_{ItemType::Apple},
    image_dir_(":/res/apple_icon.png"),
    sound_dir_(":/res/apple_eat.mp3"),
    item_icon_(image_dir_.fileName()),
    item_sound_(sound_dir_.fileName())

{

//    QPicture img;
//    img.load(image_dir_.absoluteFilePath());
//    ui->img_lbl->setPicture(img);
}

Item::~Item() {
    //delete ui;
}

void Item::EatSound() {
    item_sound_.play();
}

void Item::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect obl(0, 0, width(), height());
    painter.drawPixmap(obl, item_icon_.pixmap(50,50));
}

void Item::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
         drag_start_position_ = event->pos();
}

void Item::mouseMoveEvent(QMouseEvent *event) {

    if (!(event->buttons() & Qt::LeftButton)) { return; }

//    if ((event->pos() - drag_start_position_).manhattanLength()
//         < QApplication::startDragDistance())
//        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;

//    mimeData->setData(mimeType, data);
    drag->setMimeData(mimeData);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);

}
