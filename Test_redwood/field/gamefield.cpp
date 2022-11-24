#include "gamefield.h"
#include "ui_gamefield.h"
#include "item.h"
//#include "inventory.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField) {
    ui->setupUi(this);
    connect(ui->main_btn, SIGNAL(clicked()), SIGNAL(showMenu()));
    connect(ui->main_btn, SIGNAL(clicked()), SIGNAL(setEnabled()));
    ui->inventory_wgt->setParent(this);
}

GameField::~GameField() { delete ui; }

void GameField::on_inventory_wgt_cellClicked(int row, int column) {
    auto item = ui->inventory_wgt->item(row, column);
    if (item) {
        QVariant val = item->data(Qt::EditRole);
        if (val.) {
            int num = val.toInt();
            if (val.toInt() > 1) {
                item->setData(Qt::EditRole, num-1);
            } else {
                item->setData(Qt::EditRole, "");
            }
        } else {
            ui->inventory_wgt->removeCellWidget(row, column);
        }
    } else {
        item = new  QTableWidgetItem();
//        QIcon ico;
        QResource res;
    //    res.registerResource()
//        ico.addFile(":/res/apple_icon.png");
        item->setBackground(QBrush(QPixmap(":/res/apple_icon.png")));
        item->setWhatsThis("Apple");
        int num = 5;
        item->setData(Qt::EditRole, num);
        ui->inventory_wgt->setItem(row, column, item);

    }

}
