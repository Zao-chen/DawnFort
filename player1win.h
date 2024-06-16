#ifndef PLAYER1WIN_H
#define PLAYER1WIN_H

#include <QWidget>

namespace Ui {
class Player1win;
}

class Player1win : public QWidget
{
    Q_OBJECT

public:
    explicit Player1win(QWidget *parent = nullptr);
    ~Player1win();

private:
    Ui::Player1win *ui;
};

#endif // PLAYER1WIN_H
