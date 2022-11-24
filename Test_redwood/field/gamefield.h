#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class GameField;
}

class GameField : public QWidget
{
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = nullptr);
    ~GameField();

private slots:

    void on_inventory_wgt_itemClicked(QTableWidgetItem *item);

    void on_inventory_wgt_currentItemChanged(QTableWidgetItem *current, QTableWidgetItem *previous);

signals:
    void showMenu();

private:
    Ui::GameField *ui;
};

#endif // GAMEFIELD_H
