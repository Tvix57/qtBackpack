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
    virtual void dragEnterEvent(QDragEnterEvent * event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragLeaveEvent(QDragLeaveEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    void AddItem(QPoint, const QMimeData *);
    void RemoveItem(QPoint&);
    QPoint GetItemPosition(QPoint);

};

#endif // INVENTORY_H
