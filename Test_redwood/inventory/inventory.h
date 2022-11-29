#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include <QTableWidget>
#include <QMouseEvent>
#include <QHeaderView>
#include <QScrollBar>
#include "database.h"

#define ROW_HEIGHT 50
#define COLUMN_WIDHT 50

class Inventory : public QTableWidget
{
    Q_OBJECT

public:
    explicit Inventory(DataBase * db_source = nullptr, QWidget *parent = nullptr);
    ~Inventory();
    const int &GetRows() const;
    const int &GetColumns() const;
    void SetRows(int);
    void SetColumns(int);
    void SetDataBaseSource(DataBase *);

protected:
    virtual void dragEnterEvent(QDragEnterEvent * event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragLeaveEvent(QDragLeaveEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;

private:
    void AddItem(QPoint, const QMimeData *);
    void MoveItem(QPoint, QPoint);
    void RemoveItem(QPoint&);
    QPoint GetItemPosition(QPoint);
    void WriteDB();
    void ReadDB();
    void SetInventorySettings();
    void ReplaceItems(QPoint&, QPoint&);
    int rows_, columns_;
    DataBase * db_source_;

};

#endif // INVENTORY_H
