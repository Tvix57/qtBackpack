#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
    delete game_field_;
}

void MainWindow::on_exit_btn_clicked() { this->close(); }


void MainWindow::on_new_game_btn_clicked() {
    game_field_ = new GameField();
    connect(game_field_, SIGNAL(showMenu()), this, SLOT(show()));
    this->hide();
    game_field_->show();
}
