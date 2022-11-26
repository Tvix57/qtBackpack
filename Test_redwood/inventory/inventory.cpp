#include "inventory.h"
#include "item.h"

Inventory::Inventory(QWidget *parent) :
    QTableWidget(parent)
{
    setDragEnabled(true);
    setAcceptDrops(true);
    setDragDropMode(QAbstractItemView::DragDrop);
}

void Inventory::mousePressEvent(QMouseEvent *event) {
    QPoint info = GetItemPosition(event->pos());
    QTableWidgetItem * item_in_inventory = item(info.x(), info.y());
    if (item_in_inventory) {
        int id = item_in_inventory->data(Qt::UserRole).toInt();
        int count = item_in_inventory->data(Qt::DisplayRole).toInt();


        if (event->button() == Qt::LeftButton) {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            mimeData->setData("ItemId", QVariant(id).toByteArray());
            mimeData->setData("ItemCount", QVariant(count).toByteArray());

            drag->setMimeData(mimeData);

            drag->setPixmap(item_in_inventory->background().texture());

            drag->exec(Qt::MoveAction);

        } else
        if (event->button() == Qt::RightButton) {
            if (count > 1) {
//                Item(id).PlaySound();
                --count;
                item_in_inventory->setData(Qt::DisplayRole, count);
            } else {
                RemoveItem(info);
            }
        }
    }
    event->accept();
}

void Inventory::dragEnterEvent(QDragEnterEvent *event) {
    event->acceptProposedAction();
}

void Inventory::dragMoveEvent(QDragMoveEvent *event) {
    event->acceptProposedAction();
}

void Inventory::dropEvent(QDropEvent *event) {
    QPoint point = GetItemPosition(event->pos());
//    if (point.isNull()) { //// необходимо проверить чтобы не в той же точке
        auto item_in_inventory = item(point.x(), point.y());
        if (event->dropAction() == Qt::MoveAction) {
            qDebug() << event->pos();
        }
        AddItem(point, item_in_inventory, event->mimeData());
        event->accept();
//    }
}

void Inventory::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}

void Inventory::AddItem(QPoint point, QTableWidgetItem *item_in_inventory, const QMimeData *data_input) {
    if (item_in_inventory == nullptr) {
        int num = QVariant(data_input->data("ItemCount")).toInt();
        int id = QVariant(data_input->data("ItemId")).toInt();
        Item * item = new Item(this);
        item_in_inventory = new  QTableWidgetItem();
        item_in_inventory->setFlags(Qt::ItemIsDragEnabled |
                                    Qt::ItemIsDropEnabled |
                                    Qt::ItemIsEditable |
                                    Qt::ItemIsEnabled);

        item_in_inventory->setBackground(QBrush(item->GetIcon().pixmap(50,50)));
        item_in_inventory->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
        item_in_inventory->setData(Qt::DisplayRole, num);
        item_in_inventory->setData(Qt::UserRole, id);
        setItem(point.x(), point.y(), item_in_inventory);
        delete item;
    } else {
        int id = QVariant(data_input->data("ItemId")).toInt();
        int num = QVariant(data_input->data("ItemCount")).toInt();
        if (item_in_inventory->data(Qt::UserRole).toInt() == id) {
            num += item_in_inventory->data(Qt::DisplayRole).toInt();
            item_in_inventory->setData(Qt::DisplayRole, num);
        }
    }
}

void Inventory::RemoveItem(QPoint &point) {
    auto item_in_inventory = item(point.x(), point.y());
    if (item_in_inventory) {
        delete item_in_inventory;
        setItem(point.x(), point.y(), nullptr);
    }
}

QPoint Inventory::GetItemPosition(QPoint input_point) {
    QPoint out_point;
    out_point.setX(input_point.y() / rowHeight(0));
    out_point.setY(input_point.x() / columnWidth(0));
    return out_point;
}
