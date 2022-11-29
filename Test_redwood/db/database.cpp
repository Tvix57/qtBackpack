#include "database.h"

DataBase::DataBase(QObject *parent) :
                    QObject(parent),
                    db_{QSqlDatabase::addDatabase("QSQLITE")},
                    file_path_ {QDir::currentPath()+QString("/items_database.sqlite")} {

    file_path_ = "/Users/ajhin/github/test_redwood/Test_redwood/db/items_database.sqlite";
    QFileInfo checkFile(file_path_);
    if (checkFile.isFile()) {
        db_.setDatabaseName(file_path_);
        if (!db_.isOpen()) {
            if (!db_.open()) {
                    qDebug() << "База данных не открылась" << db_.lastError();
            }
        }
    }
}

DataBase::~DataBase() {
    db_.close();
}

QHash<QString, QVariant> DataBase::GetItemData(int row_id) {
    QHash<QString, QVariant> result;
    QSqlQuery query(db_);
    query.prepare("SELECT * FROM items WHERE id = ' " + QString::number(row_id)+ " ' ");
    if (query.exec()) {
        if (query.first()) {
            QSqlRecord record_gr = query.record();
            result.insert("id", row_id);
            result.insert("item_type", query.value(record_gr.indexOf("item_type")));
            result.insert("icon_way", query.value(record_gr.indexOf("icon_way")));
            result.insert("sound_way", query.value(record_gr.indexOf("sound_way")));
        }
    }
 return result;
}

QMap<int, QHash<QString, QVariant>> DataBase::GetInventoryData() {
    QMap<int, QHash<QString, QVariant>> result;
    QSqlQuery query(db_);
    query.prepare("SELECT * FROM inventory");
    if (query.exec()) {
        if (query.first()) {
            do {
                QSqlRecord record_gr = query.record();
                int position = query.value(record_gr.indexOf("item_position")).toInt();
                QHash <QString, QVariant> tmp;
                tmp.insert("item_id", query.value(record_gr.indexOf("item_id")));
                tmp.insert("item_type", query.value(record_gr.indexOf("item_type")));
                tmp.insert("item_count", query.value(record_gr.indexOf("item_count")));

                result.insert(position, tmp);
            } while (query.next());
        }
    }
    return result;
}

void DataBase::SetInventoryData(QList<QString> new_row) {
    QSqlQuery query(db_);
    QString query_row("INSERT INTO inventory (item_position, item_id, item_count)"
                      "VALUES (?, ?, ?);");

    query.prepare(query_row);
    for (int i = 0; i < 3; i++) {
        query.bindValue(i, new_row.at(i));
    }
    query.exec();
}

void DataBase::ClearInventoryDB() {
    QSqlQuery query(db_);
    query.exec("TRUNCATE TABLE inventory");
}

