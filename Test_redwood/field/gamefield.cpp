#include "gamefield.h"
#include "ui_gamefield.h"
#include "item.h"
//#include "inventory.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField) {
    ui->setupUi(this);
    connect(ui->main_btn, SIGNAL(clicked()), SIGNAL(showMenu()));
//    connect(ui->main_btn, SIGNAL(clicked()), SIGNAL(setEnabled()));
    ui->inventory_wgt->setParent(this);
}

GameField::~GameField() { delete ui; }
