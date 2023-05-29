#ifndef PLAYER2WIN_H
#define PLAYER2WIN_H

#include <QWidget>

namespace Ui {
class Player2win;
}

class Player2win : public QWidget
{
    Q_OBJECT

public:
    explicit Player2win(QWidget *parent = nullptr);
    ~Player2win();

private:
    Ui::Player2win *ui;
};

#endif // PLAYER2WIN_H
