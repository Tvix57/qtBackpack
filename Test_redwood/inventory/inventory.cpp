#include "inventory.h"
#include "item.h"

Inventory::Inventory(QWidget *parent) :
    QTableWidget(parent)
{
    connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(RemoveItem(int,int)));
//    for (auto &it, items()) {
//        setItem(0,0, nullptr);
//    }

}

//void Inventory::mousePressEvent(QMouseEvent *event) {
//    if (event->button() == Qt::RightButton ) {

//    }
//}

void Inventory::dropEvent(QDropEvent *event) {
//    event->mimeData()
    //    item(event->pos());
}

void Inventory::RemoveItem(int row, int column) {
    auto item_in_inventory = item(row, column);
    if (item_in_inventory) {
        QVariant val = item_in_inventory->data(Qt::EditRole);
        if (val.type() == 2) {
            int num = val.toInt();
            if (num > 1) {
                item_in_inventory->setData(Qt::EditRole, num-1);
            } else {
                item_in_inventory->setData(Qt::EditRole, "");
            }
        } else {
            setItem(row, column, nullptr);
            delete item_in_inventory;
        }
    } else {
        item_in_inventory = new  QTableWidgetItem();
//        QIcon ico;
        QResource res;
    //    res.registerResource()
//        ico.addFile(":/res/apple_icon.png");
        item_in_inventory->setBackground(QBrush(QPixmap(":/res/apple_icon.png")));
        item_in_inventory->setWhatsThis("Apple");
        int num = 5;
        item_in_inventory->setData(Qt::EditRole, num);
        setItem(row, column, item_in_inventory);

    }
}

//void Inventory::on_table_wgt_itemClicked(QTableWidgetItem *item) {
//    if (item) {
//        auto info = item->flags();
//    }


//}

//void Inventory::on_table_wgt_itemChanged(QTableWidgetItem *item)
//{
//    auto test = item->flags();
//}


