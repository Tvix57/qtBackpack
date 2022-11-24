#include "gamefield.h"
#include "ui_gamefield.h"
#include "item.h"
//#include "inventory.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);
    connect(ui->main_btn, SIGNAL(clicked()), SIGNAL(showMenu()));

}

GameField::~GameField() { delete ui; }

void GameField::on_inventory_wgt_itemClicked(QTableWidgetItem *item) {
    if (item) {

        item->setWhatsThis("Apple");
        int num = item->data(Qt::EditRole).toInt();
        item->setData(Qt::EditRole, num+1);
    } else {

         item = new  QTableWidgetItem();
        QIcon ico;
        QResource res;
    //    res.registerResource()
        ico.addFile(":/res/apple_icon.png");
    //    item->setIcon(ico);

        item->setWhatsThis("Apple");
        int num = 1;
        item->setData(Qt::EditRole, num);
//        setItem(0, 0, item);

//        item = new  QTableWidgetItem();
//        item->setWhatsThis("Apple");
//        num = 2;
//        item->setData(Qt::EditRole, num);
//        this->setItem(0, 1, item);

//        item = new  QTableWidgetItem();
    //    QIcon ico;
    //    QResource res;
    //    res.registerResource()
//        ico.addFile(":/res/water_icon.png");
//        item->setIcon(ico);
//        item->setWhatsThis("Water");
//        setItem(1, 1, item);


    }
}

void GameField::on_inventory_wgt_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous)
{
    if (current && previous) {
        if(current->whatsThis() == previous->whatsThis()) {
            int cur_num = current->data(Qt::EditRole).toInt() + previous->data(Qt::EditRole).toInt();
            current->setData(Qt::EditRole, cur_num);
        }
    }
}
