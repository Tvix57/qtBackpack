#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QResource>
#include <QPicture>
#include <QSound>
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

enum ItemType {
    Apple,
    Water
};

namespace Ui {
class Item;
}

class Item : public QWidget
{
    Q_OBJECT

public:
    explicit Item(QWidget *parent = nullptr);
//    Item(QWidget *parent = nullptr, QSound item_sound);
    ~Item();
    void EatSound();

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    ItemType type_;
    QResource image_dir_;
    QResource sound_dir_;
    QIcon item_icon_;
    QSound item_sound_;
    QPoint drag_start_position_;
};

#endif // ITEM_H
