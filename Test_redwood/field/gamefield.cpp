#include "gamefield.h"
#include "ui_gamefield.h"
#include "item.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField) {
    ui->setupUi(this);
    connect(ui->main_btn, SIGNAL(clicked()), SIGNAL(showMenu()));
    ui->gridLayout->addWidget(new Item(this), 1,0);
    ui->inventory_wgt->setParent(this);
}

GameField::~GameField() { delete ui; }

void GameField::on_comboBox_currentIndexChanged(int index) {
    ui->gridLayout->removeWidget(ui->gridLayout->itemAtPosition(1,0)->widget());
    ui->gridLayout->addWidget(new Item(index, this), 1,0);
}
