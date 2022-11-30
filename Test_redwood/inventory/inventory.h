#ifndef INVENTORY_H
#define INVENTORY_H

#include <QWidget>
#include <QTableWidget>
#include <QMouseEvent>
#include <QHeaderView>
#include <QScrollBar>

#include "database.h"

#define ROW_HEIGHT 51
#define COLUMN_WIDHT 51

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
    //установка указателя на акутального менеджера БД

protected:
    virtual void dragEnterEvent(QDragEnterEvent * event) override;
    virtual void dragMoveEvent(QDragMoveEvent *event) override;
    virtual void dropEvent(QDropEvent *event) override;
    virtual void dragLeaveEvent(QDragLeaveEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    void AddItem(QPoint, const QMimeData *);
    //добавление нового предмета в tabWidget на основе данных полученных из mimedata;
    void MoveItem(QPoint, const QMimeData *);
    //функция
    void RemoveItem(QPoint&);
    //удаление предмета из таблицы
    QPoint GetItemPosition(QPoint);
    // получение табличных координат предмета или события в таблице
    void WriteDB();
    //загрузка данных В бд
    void ReadDB();
    // //загрузка данных ИЗ бд
    void SetInventorySettings();
    // установка настроек виджета таблицы
    void ReplaceItems(QPoint&, const QMimeData *);
    // функция свапа элементов таблицы с разными id
    int rows_, columns_;
    DataBase * db_source_;
};

#endif // INVENTORY_H
