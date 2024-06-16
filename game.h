#ifndef GAME_H
#define GAME_H

#include <QWidget>
#include <QKeyEvent>
#include <QTimer>
#include <player1win.h>
#include <player2win.h>

#include <QTimer>
#include <QTime>



namespace Ui {
class game;
}

class game : public QWidget
{
    Q_OBJECT

public:
    explicit game(QWidget *parent = nullptr);
    Player1win *p1w;
    Player2win *p2w;

    virtual void timerEvent(QTimerEvent *e);

    ~game();



protected:
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    Ui::game *ui;
    QList<int> keys;
    QTimer* keyRespondTimer;
    int hp_player1=100;
    int hp_player2=100;
    void slowTimeOut();


};

#endif // GAME_H
