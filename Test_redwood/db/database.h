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
    QMap<int, QHash<QString, QVariant>> GetInventoryData();
    void SetInventoryData(QList<QString>);
    void ClearInventoryDB();


private:
    QSqlDatabase db_;
    QString file_path_;
};

#endif // DATABASE_H
