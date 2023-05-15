#include "game.h"
#include "ui_game.h"
#include <QDebug>


game::game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
}

game::~game()
{
    delete ui;
}

void game::keyPressEvent(QKeyEvent * event)
{
    switch (event->key())
    {
        // ESC键
        case Qt::Key_W:
            player1_y-=2;
            ui->label_player1->move(player1_x,player1_y);
        break;
        case Qt::Key_S:
            player1_y+=2;
            ui->label_player1->move(player1_x,player1_y);
        break;
        case Qt::Key_A:
            player1_x-=2;
            ui->label_player1->move(player1_x,player1_y);
        break;
        case Qt::Key_D:
            player1_x+=2;
            ui->label_player1->move(player1_x,player1_y);
        break;
    }
    switch (event->key())
    {
        // ESC键
        case Qt::Key_Up:
            player2_y-=2;
            ui->label_player2->move(player2_x,player2_y);
        break;
        case Qt::Key_Down:
            player2_y+=2;
            ui->label_player2->move(player2_x,player2_y);
        break;
        case Qt::Key_Left:
            player2_x-=2;
            ui->label_player2->move(player2_x,player2_y);
        break;
        case Qt::Key_Right:
            player2_x+=2;
            ui->label_player2->move(player2_x,player2_y);
        break;
    }
}

// 键盘释放事件
