#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QTableWidgetItem>

#include "inventory.h"
#include "item.h"

namespace Ui {
class GameField;
}

class GameField : public QWidget
{
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = nullptr);
    ~GameField();

signals:
    void showMenu();

private slots:
    void on_comboBox_currentIndexChanged(int index);
    void on_main_btn_clicked();

private:
    Ui::GameField *ui;
    DataBase * db_source_;
    Inventory * inventory_;
};

#endif // GAMEFIELD_H
