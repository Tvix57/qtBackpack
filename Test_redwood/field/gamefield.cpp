#include "gamefield.h"
#include "ui_gamefield.h"
#include "item.h"
//#include "inventory.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField)
{
    ui->setupUi(this);
    ui->item_wgt->show();
    ui->inventory_wgt->show();
    connect(ui->main_btn, SIGNAL(clicked()), SIGNAL(showMenu()));
}

GameField::~GameField()
{
    delete ui;
}

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
