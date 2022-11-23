#include "gamefield.h"
#include "ui_gamefield.h"
#include "item.h"
#include "inventory.h"

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
