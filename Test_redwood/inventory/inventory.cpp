#include "inventory.h"
#include "item.h"

Inventory::Inventory(QWidget *parent) :
    QTableWidget(parent)
{
    connect(this, SIGNAL(cellClicked(int, int)), this, SLOT(RemoveItem(int,int)));/////
    setDragEnabled(true);
    setAcceptDrops(true);
    setDropIndicatorShown(true);
}

//void Inventory::mousePressEvent(QMouseEvent *event) {
////    if (event->button() == Qt::LeftButton) {
////        QPoint info = event->pos();

////        int num = 5;
////        QDrag *drag = new QDrag(this);
////        QMimeData *mimeData = new QMimeData;
////        mimeData->setImageData(item(0,0)->data(Qt::DisplayRole).value<Item*>().GetIcon());
////        mimeData->setData("Item*", item(0,0)->data(Qt::DisplayRole).toByteArray());

////        drag->setMimeData(mimeData);
////        Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);

////    } else
//    if (event->button() == Qt::RightButton) {
//        RemoveItem(0,0);
//    }
//    event->accept();
//}

void Inventory::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void Inventory::dragMoveEvent(QDragMoveEvent *event) {
    event->accept();
}

void Inventory::dropEvent(QDropEvent *event) {
    if(event->source() == this) {
        event->setDropAction(Qt::DropAction::MoveAction);
    }
    QTableWidget::dropEvent(event);
}

bool Inventory::dropMimeData (int row, int column, const QMimeData *data_input, Qt::DropAction action) {
    QPoint point(row, column);
    auto item_in_inventory = item(row, column);
    if (data_input->hasFormat("Item*")) {
      AddItem(point, item_in_inventory, data_input);
    } else if (action == Qt::DropAction::MoveAction) {
      SummNReolaceItem(point, item_in_inventory, data_input);
    }
    return true;
}

void Inventory::dragLeaveEvent(QDragLeaveEvent *event) {
    clear();
    event->accept();
}

void Inventory::AddItem(QPoint point, QTableWidgetItem *item_in_inventory, const QMimeData *data_input) {
    if (item_in_inventory == nullptr) {
        item_in_inventory = new  QTableWidgetItem();
//            QByteArray arr = data_input->data("Item*");
//            QVariant var(arr);
//            QIcon icon =  var.value<Item*>()->GetIcon();
//            item_in_inventory->setIcon(icon);
        int num = 5;


        item_in_inventory->setData(Qt::EditRole, num);
        setItem(point.x(), point.y(), item_in_inventory);
        QModelIndex in = indexAt(point);
        setIndexWidget(in, new Item);
//            item_in_inventory->setData(Qt::DisplayRole, data_input->data("Item"));
    } else {
        int num = item_in_inventory->data(Qt::EditRole).toInt();
        item_in_inventory->setData(Qt::EditRole, num+1);

        setIndexWidget(indexAt(point), new Item);
    }
}

void Inventory::SummNReolaceItem(QPoint point, QTableWidgetItem *item_in_inventory, const QMimeData *data_input) {
    QByteArray arr = data_input->data("application/x-qabstractitemmodeldatalist");
    QVariant var(data_input->data("application/x-qabstractitemmodeldatalist"));
    QTableWidgetItem *item_in_inventory2 = var.value<QTableWidgetItem *>();
    if (item_in_inventory == nullptr) {

    } else {
      int num = item_in_inventory->data(Qt::EditRole).toInt();
      num += data_input->data("application/x-qabstractitemmodeldatalist").toInt();
      item_in_inventory->setData(Qt::EditRole, num);
    }
}

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
    }
}
