#include "inventory.h"
#include "item.h"

Inventory::Inventory(QWidget *parent) :
    QTableWidget(parent)
{
    connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(RemoveItem(int,int)));
    setAcceptDrops(true);
}

void Inventory::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        QPoint info = event->pos();
//        event->
        int num = 5;
        QDrag *drag = new QDrag(this);
        QMimeData *mimeData = new QMimeData;
//        mimeData->setImageData(item(0,0)->data(Qt::DisplayRole).value<Item>().GetIcon());
//        mimeData->setData("Item", item(0,0)->data(Qt::DisplayRole).toByteArray());
        drag->setMimeData(mimeData);
        Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
    } else if (event->button() == Qt::RightButton) {
        RemoveItem(0,0);
    }

}

bool Inventory::dropMimeData (int row, int column, const QMimeData *data_input, Qt::DropAction action) {
    qDebug() << "test dropMimeData";
    if (data_input->hasFormat("Item")) {

        auto item_in_inventory = item(row, column);
        if (item_in_inventory == nullptr) {
            item_in_inventory = new  QTableWidgetItem();

    //        item_in_inventory->setIcon(event->mimeData()->imageData().value< QIcon >());
            int num = 5;
            item_in_inventory->setData(Qt::EditRole, num);
            item_in_inventory->setData(Qt::DisplayRole, data_input->data("Item"));

        } else {
            int num = item_in_inventory->data(Qt::EditRole).toInt();
            item_in_inventory->setData(Qt::EditRole, num+1);
        }

    }
    return true;
}

//void Inventory::dropEvent(QDropEvent *event) {
//    if (event->mimeData()->hasFormat("Item")) {
//        QPoint info = event->pos();
//        auto item_in_inventory = item(drop_position_.x(), drop_position_.y());
//        if (item_in_inventory == nullptr) {
//            item_in_inventory = new  QTableWidgetItem();
////            QVariant data = event->mimeData()->data("Item");
//    //        item_in_inventory->setIcon(event->mimeData()->imageData().value< QIcon >());
//            int num = 5;
//            item_in_inventory->setData(Qt::EditRole, num);



//        } else {
//            int num = item_in_inventory->data(Qt::EditRole).toInt();
//            item_in_inventory->setData(Qt::EditRole, num+1);
//        }

//      event->acceptProposedAction();
//    }
//}

void Inventory::RemoveItem(int row, int column) {
    auto item_in_inventory = item(row, column);
    if (item_in_inventory) {
        QVariant val = item_in_inventory->data(Qt::EditRole);
        if (val.typeId() == 2) {
            int num = val.toInt();
            if (num > 1) {
                item_in_inventory->setData(Qt::EditRole, num-1);
            } else {
                item_in_inventory->setData(Qt::EditRole, "");
            }
        } else {
            setItem(row, column, nullptr);
//            delete item_in_inventory;
        }
    } else {
//        item_in_inventory = new  QTableWidgetItem();
////        QIcon ico;
//        QResource res;
//    //    res.registerResource()
////        ico.addFile(":/res/apple_icon.png");
//        item_in_inventory->setBackground(QBrush(QPixmap(":/res/apple_icon.png")));
//        item_in_inventory->setWhatsThis("Apple");
//        int num = 5;
//        item_in_inventory->setData(Qt::EditRole, num);
//        setItem(row, column, item_in_inventory);

    }
}
