#include "gamefield.h"
#include "ui_gamefield.h"

GameField::GameField(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GameField) {
    ui->setupUi(this);
    db_source_ = new DataBase(this);

    Item * item = new Item(this);
    item->SetDataBaseSource(db_source_);
    inventory_ = new Inventory(db_source_, this);

    ui->gridLayout->addWidget(item, 2,0);
    ui->gridLayout->addWidget(inventory_, 1, 1, 2, 1);
}

GameField::~GameField() { delete ui;
                          delete inventory_;
                          delete db_source_;}

void GameField::on_comboBox_currentIndexChanged(int index) {
    ui->gridLayout->removeWidget(ui->gridLayout->itemAtPosition(2,0)->widget());
    Item * item = new Item(this);
    item->SetDataBaseSource(db_source_);
    item->SetItem(index);
    ui->gridLayout->addWidget(item, 2,0);
}

void GameField::on_main_btn_clicked() {
//    ui->gridLayout->setEnabled(false);
    emit showMenu();
}
