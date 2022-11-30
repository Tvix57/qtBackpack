#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "gamefield.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_exit_btn_clicked();

    void on_new_game_btn_clicked();
    void CreateNewGameField();

private:
    Ui::MainWindow *ui;
    GameField * game_field_;
};
#endif // MAINWINDOW_H
