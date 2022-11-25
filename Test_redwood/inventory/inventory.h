#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include <QTableWidget>
#include <QMouseEvent>

namespace Ui {
class Inventory;
}

class Inventory : public QTableWidget
{
    Q_OBJECT

public:
    explicit Inventory(QWidget *parent = nullptr);
//    ~Inventory();
//    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;

private slots:
    void RemoveItem(int row, int column);

};

#endif // INVENTORY_H
