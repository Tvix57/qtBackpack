#include "inventory.h"
#include "item.h"

Inventory::Inventory(DataBase* db_source, QWidget *parent) :
    QTableWidget(parent),
    rows_{3},
    columns_{3},
    db_source_{db_source}
{
    SetInventorySettings();
    ReadDB();
}

Inventory::~Inventory() {
    WriteDB();
}

void Inventory::mousePressEvent(QMouseEvent *event) {
    QPoint item_position = GetItemPosition(event->pos());
    QTableWidgetItem * item_in_inventory = item(item_position.x(), item_position.y());
    if (item_in_inventory) {
        int id = item_in_inventory->data(Qt::UserRole).toInt();
        int count = item_in_inventory->data(Qt::DisplayRole).toInt();
        if (event->button() == Qt::LeftButton) {
            QDrag *drag = new QDrag(this);
            QMimeData *mimeData = new QMimeData;
            item_in_inventory = takeItem(item_position.x(), item_position.y());
            mimeData->setData("ItemId", QVariant(id).toByteArray());
            mimeData->setData("ItemCount", QVariant(count).toByteArray());
            mimeData->setData("StartPointX" , QVariant(item_position.x()).toByteArray());
            mimeData->setData("StartPointY" , QVariant(item_position.y()).toByteArray());

            drag->setMimeData(mimeData);
            drag->setPixmap(item_in_inventory->background().texture());

            drag->exec(Qt::MoveAction);
        }
    }
    event->accept();
}

void Inventory::mouseReleaseEvent(QMouseEvent *event) {
    QPoint item_position = GetItemPosition(event->pos());
    QTableWidgetItem * item_in_inventory = item(item_position.x(), item_position.y());
    if (item_in_inventory) {
        int id = item_in_inventory->data(Qt::UserRole).toInt();
        int count = item_in_inventory->data(Qt::DisplayRole).toInt();
        if (event->button() == Qt::RightButton) {
                Item *tmp = new Item(this);
                tmp->SetDataBaseSource(db_source_);
                tmp->SetItem(id);
                tmp->PlaySound();
                if (count > 1) {
                    --count;
                    item_in_inventory->setData(Qt::DisplayRole, count);
                } else {
                    RemoveItem(item_position);
                }
        }
    }
    event->accept();
}

const int &Inventory::GetRows() const {
    return rows_;
}

const int &Inventory::GetColumns() const {
    return columns_;
}

void Inventory::SetRows(int new_rows) {
    rows_ = new_rows;
    setRowCount(rows_);
}

void Inventory::SetColumns(int new_columns) {
    columns_ = new_columns;
    setColumnCount(columns_);
}

void Inventory::SetDataBaseSource(DataBase * db_source) {
    db_source_ = db_source;
}

void Inventory::dragEnterEvent(QDragEnterEvent *event) {    
    event->acceptProposedAction();
}

void Inventory::dragMoveEvent(QDragMoveEvent *event) {
    event->acceptProposedAction();
}

void Inventory::dropEvent(QDropEvent *event) {
    if (event->mimeData()->hasFormat("ItemId")) {
        QPoint drop_point = GetItemPosition(event->pos());
        if (event->dropAction() == Qt:: MoveAction) {
            if (event->mimeData()->hasFormat("StartPointX") &&
                event->mimeData()->hasFormat("StartPointY")) {
                QPoint start_point (QVariant(event->mimeData()->data("StartPointX")).toInt(),
                                    QVariant(event->mimeData()->data("StartPointY")).toInt());
                if (start_point != drop_point) {
                    MoveItem(drop_point, event->mimeData());
                } else {
                    AddItem(start_point, event->mimeData());
                }
                event->accept();
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
        Item * item = new Item(this);
        item->SetDataBaseSource(db_source_);
        item->SetItem(id);
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

void Inventory::MoveItem(QPoint drop_point, const QMimeData *data_input) {
    QTableWidgetItem *item_drop = item(drop_point.x(), drop_point.y());
    if (item_drop) {
        int id = QVariant(data_input->data("ItemId")).toInt();
        if (id == item_drop->data(Qt::UserRole).toInt()) {
             int num = item_drop->data(Qt::DisplayRole).toInt();
             num += QVariant(data_input->data("ItemCount")).toInt();
             item_drop->setData(Qt::DisplayRole, num);
         } else {
            ReplaceItems(drop_point, data_input);
         }
    } else {
        AddItem(drop_point, data_input);
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

void Inventory::WriteDB() {
    db_source_->ClearInventoryDB();
    for(int i = 0; i < rows_; ++i) {
        for(int j = 0; j < columns_; ++j) {
            QTableWidgetItem * cur_item = item(i,j);
            if (cur_item) {
                QList<QString> list;
                list << QString::number(i * rows_ + j);
                list << cur_item->data(Qt::UserRole).toString();
                list << cur_item->data(Qt::DisplayRole).toString();
                db_source_->SetInventoryData(list);
            }
        }
    }
}

void Inventory::ReadDB() {
    auto db_data = db_source_->GetInventoryData();
    for (auto item = db_data.begin(); item!=db_data.end(); item++) {
        QMimeData tmp_data;
        QPoint position;
        position.setX(item.key() / rows_);
        position.setY(item.key() % rows_);
        tmp_data.setData("ItemId", QVariant(item->value("item_id").toInt()).toByteArray());
        tmp_data.setData("ItemCount", QVariant(item->value("item_count").toInt()).toByteArray());
        AddItem(position, &tmp_data);
    }
}

void Inventory::SetInventorySettings() {
    setRowCount(rows_);
    setColumnCount(columns_);

    horizontalHeader()->setDefaultSectionSize(COLUMN_WIDHT);
    horizontalHeader()->setVisible(false);
    horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    horizontalScrollBar()->setDisabled(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    verticalHeader()->setDefaultSectionSize(ROW_HEIGHT);
    verticalHeader()->setVisible(false);
    verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    verticalScrollBar()->setDisabled(true);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    setFixedSize((ROW_HEIGHT)*rows_, (COLUMN_WIDHT)*columns_);
    setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

    setDragEnabled(true);
    setAcceptDrops(true);
    setDragDropMode(QAbstractItemView::DragDrop);
}

void Inventory::ReplaceItems(QPoint & curent_point, const QMimeData * data_input) {
    QTableWidgetItem * cur_item = takeItem(curent_point.x(), curent_point.y());
    AddItem(curent_point, data_input);
    QPoint start_point (QVariant(data_input->data("StartPointX")).toInt(),
                        QVariant(data_input->data("StartPointY")).toInt());
    setItem(start_point.x(), start_point.y(), cur_item);
}
