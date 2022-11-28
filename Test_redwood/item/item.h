#ifndef ITEM_H
#define ITEM_H

#include <QWidget>
#include <QResource>
#include <QtSql>
#include <QTableView>
#include <QIcon>
#include <QPainter>
#include <QMouseEvent>
#include <QDrag>
#include <QMimeData>
#include <QSoundEffect>

class Item : public QWidget
{
    Q_OBJECT

public:
    explicit Item(QWidget *parent = nullptr);
    Item(int item_id, QWidget *parent = nullptr);
    ~Item();
    void PlaySound();
    const QIcon &GetIcon() const;
    void SetIcon(QIcon);
    const QString &GetItemType() const;
    void SetItemType(QString);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    bool OpenDb();
    int id_;
    QString item_type_;
    QResource image_dir_;
    QResource sound_dir_;
    QIcon item_icon_;
    QSoundEffect *item_sound_;
};


Q_DECLARE_METATYPE(Item*);

#endif // ITEM_H
