#include "item.h"

Item::Item(QWidget *parent) :
    QWidget(parent),
    id_{0},
    item_type_{"Apple"},
    image_dir_(":/res/apple_icon.png"),
    sound_dir_(":/res/apple_eat.wav"),
    item_icon_(image_dir_.fileName())
{
item_sound_ = new QSoundEffect(this);
item_sound_->setSource(QUrl::fromLocalFile(sound_dir_.absoluteFilePath()));
}

Item::Item(int item_id, QWidget *parent) :
    QWidget(parent),
    id_{item_id} {
        // sql query by id
}

Item::~Item() {
}

void Item::PlaySound() {
    if (item_sound_->status() == QSoundEffect::Ready) {
        item_sound_->play();
    }
}

const QIcon &Item::GetIcon() const {
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

void Item::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::RightButton) {
        PlaySound();
    }
    event->accept();
}

void Item::mouseMoveEvent(QMouseEvent *event) {
    if (!(event->buttons() & Qt::LeftButton)) { return; }
    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setData("ItemId", QVariant(id_).toByteArray());
    mimeData->setData("ItemCount", QVariant(1).toByteArray());
    drag->setPixmap(GetIcon().pixmap(50,50, QIcon::Normal, QIcon::On));
    drag->setMimeData(mimeData);
    drag->exec(Qt::CopyAction);
}
