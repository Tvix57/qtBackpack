#include "inventory.h"
#include "item.h"

Inventory::Inventory(QWidget *parent) :
    QTableWidget(parent)
{


}

//Inventory::~Inventory() { delete ui; }

//void Inventory::mousePressEvent(QMouseEvent *event) {
//    if (event->button() == Qt::RightButton ) {

//    }
//}

//void Inventory::dropEvent(QDropEvent *event)
//{
////    event->
//    itemAt(event->pos());
//}

//void Inventory::on_table_wgt_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous) {
//    if (current && previous) {
//        if(current->whatsThis() == previous->whatsThis()) {
//            int cur_num = current->data(Qt::EditRole).toInt() + previous->data(Qt::EditRole).toInt();
//            current->setData(Qt::EditRole, cur_num);
//        }
//    }
//}

//void Inventory::on_table_wgt_itemClicked(QTableWidgetItem *item) {
//    if (item) {
//        auto info = item->flags();
//    }


//}

//void Inventory::on_table_wgt_itemChanged(QTableWidgetItem *item)
//{
//    auto test = item->flags();
//}


