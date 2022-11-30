#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QtSql>

class DataBase : public QObject
{
    Q_OBJECT
public:
    explicit DataBase(QObject *parent = nullptr);
    ~DataBase();
    QHash<QString, QVariant> GetItemData(int);
    /*
     получение данных о предмете по id из базы данных
     возвращает хэштаблицу где ключ это имя параметра
    */
    QMap<int, QHash<QString, QVariant>> GetInventoryData();
    /*
    получение данных о предметах в рюкзаке из базы данных
    возвращает карту таблиц в которой ключ - индек ячейки в рюкзаке
    и таблица которая содержит id предмета, его тип и количество
    */
    void SetInventoryData(QList<QString>);
    /*
    загрузка новой строки данных в бд о предмете в рюкзаке
    получает список с id предметом, позицией, и количеством
    */
    void ClearInventoryDB();
    // очистка таблицы с предметами
private:
    QSqlDatabase db_;
    QString file_path_;
};

#endif // DATABASE_H
