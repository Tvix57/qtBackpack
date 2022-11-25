#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>
#include <QTableWidgetItem>

namespace Ui {
class GameField;
}

class GameField : public QWidget
{
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = nullptr);
    ~GameField();

signals:
    void showMenu();

private:
    Ui::GameField *ui;
};

#endif // GAMEFIELD_H
