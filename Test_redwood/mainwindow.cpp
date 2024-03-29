#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
      game_field_{nullptr}
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
    delete game_field_;
}

void MainWindow::on_exit_btn_clicked() {
    if (game_field_) {
        game_field_->close();
    }
    this->close();
}

void MainWindow::on_new_game_btn_clicked() {
    CreateNewGameField();
}

void MainWindow::CreateNewGameField() {
    game_field_ = new GameField();
    connect(game_field_, SIGNAL(showMenu()), this, SLOT(show()));
    this->hide();
    game_field_->show();
}

void MainWindow::on_continuebtn_clicked()
{
    if (game_field_) {
        connect(game_field_, SIGNAL(destroyed()), this, SLOT(CreateNewGameField()));
        delete game_field_;
    } else {
        CreateNewGameField();
    }
}

