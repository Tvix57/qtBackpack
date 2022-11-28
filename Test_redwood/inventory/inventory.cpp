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
            mimeData->setData("StartPointX" , QVariant(info.x()).toByteArray());
            mimeData->setData("StartPointY" , QVariant(info.y()).toByteArray());

            drag->setMimeData(mimeData);
            drag->setPixmap(item_in_inventory->background().texture());

            drag->exec(Qt::MoveAction);
        } else if (event->button() == Qt::RightButton) {
            Item *tmp = new Item(id, this);
            tmp->PlaySound();
            if (count > 1) {
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
    if (event->mimeData()->hasFormat("ItemId")) {
        QPoint drop_point = GetItemPosition(event->position().toPoint());
        if (event->dropAction() == Qt:: MoveAction) {
            if (event->mimeData()->hasFormat("StartPointX") &&
                event->mimeData()->hasFormat("StartPointY")) {
                QPoint start_point (QVariant(event->mimeData()->data("StartPointX")).toInt(),
                                    QVariant(event->mimeData()->data("StartPointY")).toInt());
                if (start_point != drop_point) {
                    MoveItem(drop_point, start_point);
                    event->accept();
                }
            }
        } else {
            AddItem(drop_point, event->mimeData());
            event->accept();
        }
    }
}

void Inventory::dragLeaveEvent(QDragLeaveEvent *event) {
    event->accept();
}

void Inventory::AddItem(QPoint drop_point, const QMimeData *data_input) {
    QTableWidgetItem *item_in_inventory = item(drop_point.x(), drop_point.y());
    int id = QVariant(data_input->data("ItemId")).toInt();
    int num = QVariant(data_input->data("ItemCount")).toInt();
    if (!item_in_inventory) {
        Item * item = new Item(id, this);
        item_in_inventory = new  QTableWidgetItem();
        item_in_inventory->setFlags(Qt::ItemIsDragEnabled |
                                    Qt::ItemIsDropEnabled |
                                    Qt::ItemIsEditable |
                                    Qt::ItemIsEnabled);
        item_in_inventory->setBackground(QBrush(item->GetIcon().pixmap(50,50)));
        item_in_inventory->setTextAlignment(Qt::AlignRight | Qt::AlignBottom);
        item_in_inventory->setData(Qt::DisplayRole, num);
        item_in_inventory->setData(Qt::UserRole, id);
        setItem(drop_point.x(), drop_point.y(), item_in_inventory);
        delete item;
    } else if (item_in_inventory->data(Qt::UserRole).toInt() == id) {
        num += item_in_inventory->data(Qt::DisplayRole).toInt();
        item_in_inventory->setData(Qt::DisplayRole, num);
    }
}

void Inventory::MoveItem(QPoint drop_point, QPoint start_point) {
    QTableWidgetItem *item_drop = item(drop_point.x(), drop_point.y());
    if (item_drop) {
         QTableWidgetItem *item_start = item(start_point.x(), start_point.y());
         if (item_start->data(Qt::UserRole).toInt() == item_drop->data(Qt::UserRole).toInt()) {
             int num = item_drop->data(Qt::DisplayRole).toInt();
             num += item_start->data(Qt::DisplayRole).toInt();
             item_drop->setData(Qt::DisplayRole, num);
             RemoveItem(start_point);
         } else {
            ReplaceItems(drop_point, start_point);
         }
    } else {
        setItem(drop_point.x(), drop_point.y(), takeItem(start_point.x(), start_point.y()));
    }
}

void Inventory::RemoveItem(QPoint &point) {
    QTableWidgetItem * item_in_inventory = item(point.x(), point.y());
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

void Inventory::ReplaceItems(QPoint & curent_point, QPoint & old_point) {
    QTableWidgetItem * cur_item = takeItem(curent_point.x(), curent_point.y());
    QTableWidgetItem * old_item = takeItem(old_point.x(), old_point.y());
    setItem(curent_point.x(), curent_point.y(), old_item);
    setItem(old_point.x(), old_point.y(), cur_item);
}
