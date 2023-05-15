#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QKeyEvent>

namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);

    ~game();



protected:
    void keyPressEvent(QKeyEvent *event);
private:
    Ui::game *ui;
    int player1_x=20,player1_y=100;
    int player2_x=1000,player2_y=100;

};

#endif // GAME_H
