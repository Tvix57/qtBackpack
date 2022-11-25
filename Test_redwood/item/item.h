#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QResource>
#include <QPicture>

//#include <QSound>
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>

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
    void PlaySound() const;
//    void SetSound(QSound);
    const QIcon &GetIcon() const;
    void SetIcon(QIcon);
    const QString &GetItemType() const;
    void SetItemType(QString);


protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QVariant sendData();
    QString item_type_;
    QResource image_dir_;
    QResource sound_dir_;
    QIcon item_icon_;
//    QSound item_sound_;
};


Q_DECLARE_METATYPE(Item);

#endif // ITEM_H
