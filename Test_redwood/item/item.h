#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QResource>
#include <QPicture>

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
    ~Item();

private:
    Ui::Item *ui;
    ItemType type;
    QResource image_dir_;

};

#endif // ITEM_H
