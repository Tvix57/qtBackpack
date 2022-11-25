#include "item.h"

Item::Item(QWidget *parent) :
    QWidget(parent),
    item_type_{"Apple"},
    image_dir_(":/res/apple_icon.png"),
    sound_dir_(":/res/apple_eat.mp3"),
    item_icon_(image_dir_.fileName())
//  ,item_sound_(sound_dir_.fileName())

{}

Item::~Item() {
}

void Item::PlaySound() const {
    //    item_sound_.play();
}

const QIcon &Item::GetIcon() const{
    return item_icon_;
}

void Item::SetIcon(QIcon new_icon) {
    item_icon_ = new_icon;
}

const QString &Item::GetItemType() const {
    return item_type_;
}

void Item::SetItemType(QString new_type) {
    item_type_ = new_type;
}

void Item::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    QRect obl(0, 0, width(), height());
    painter.drawPixmap(obl, item_icon_.pixmap(50,50));
}

void Item::mouseMoveEvent(QMouseEvent *event) {
    if (!(event->buttons() & Qt::LeftButton)) { return; }
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("Item", sendData().toByteArray());
    drag->setPixmap(item_icon_.pixmap(50,50, QIcon::Normal, QIcon::On));
    drag->setMimeData(mimeData);
    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
}

QVariant Item::sendData() {
    QVariant data;
    data.setValue(this);
    return data;
}
