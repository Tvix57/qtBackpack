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

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
//    virtual void dropEvent(QDropEvent *event) override;
    virtual bool dropMimeData (int row, int column, const QMimeData *, Qt::DropAction) override;

private:
//    QPoint drag_position_;
//    QPoint drop_position_;
private slots:
    void RemoveItem(int row, int column);

};

#endif // INVENTORY_H
