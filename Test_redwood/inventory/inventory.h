#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include <QTableWidget>

namespace Ui {
class Inventory;
}

class Inventory : public QWidget
{
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = nullptr);
    ~Inventory();

private slots:
    void on_table_wgt_itemClicked(QTableWidgetItem *item);

private:
    Ui::Inventory *ui;
};

#endif // INVENTORY_H
