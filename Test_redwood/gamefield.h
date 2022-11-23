#ifndef GAMEFIELD_H
#define GAMEFIELD_H

#include <QWidget>

namespace Ui {
class GameField;
}

class GameField : public QWidget
{
    Q_OBJECT

public:
    explicit GameField(QWidget *parent = nullptr);
    ~GameField();

private:
    Ui::GameField *ui;
};

#endif // GAMEFIELD_H
