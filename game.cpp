#include "game.h"
#include "ui_game.h"
#include <QDebug>
#include <QtMath>
#include <player1win.h>
#include <player2win.h>

bool on_player1=false;
bool on_player2=false;


game::game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    keyRespondTimer = new QTimer(this);
    connect(keyRespondTimer, &QTimer::timeout, this, &game::slowTimeOut); //按键信号
}

game::~game()
{
    delete ui;
}
void game::keyPressEvent(QKeyEvent *event){
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的按下,就将key值加入容器
        keys.append(event->key());
    if(!keyRespondTimer->isActive()) //如果定时器不在运行，就启动一下
        keyRespondTimer->start(4);
}
void game::keyReleaseEvent(QKeyEvent *event){
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的释放,就将key值从容器中删除
        keys.removeAll(event->key());
    if(keys.isEmpty()) //容器空了，关闭定时器
        keyRespondTimer->stop();
}


void game::slowTimeOut(){ //输入按键
    foreach (int key, keys) {
        switch (key) {
        /*玩家1*/
        case Qt::Key_W:
            ui->label_player1->move(ui->label_player1->x(), ui->label_player1->y() - 3);
            ui->progressBar_player1->move(ui->progressBar_player1->x(), ui->progressBar_player1->y() - 3);
            break;
        case Qt::Key_A:
            ui->label_player1->move(ui->label_player1->x() - 3, ui->label_player1->y());
            ui->progressBar_player1->move(ui->progressBar_player1->x()- 3, ui->progressBar_player1->y() );
            break;
        case Qt::Key_S:
            ui->label_player1->move(ui->label_player1->x(), ui->label_player1->y() + 3);
            ui->progressBar_player1->move(ui->progressBar_player1->x(), ui->progressBar_player1->y() + 3);
            break;
        case Qt::Key_D:
            ui->label_player1->move(ui->label_player1->x() + 3, ui->label_player1->y());
            ui->progressBar_player1->move(ui->progressBar_player1->x() + 3, ui->progressBar_player1->y());
            break;
        case Qt::Key_Q:
            if((qPow(ui->label_player1->x()-ui->label_player2->x(),2)+qPow(ui->label_player1->y()-ui->label_player2->y(),2))<=2000) //攻击
            {
                if(on_player1==false)
                {
                    hp_player2-=5;
                    ui->progressBar_player2->setValue(hp_player2);
                    on_player1 = true;
                    if(hp_player2 == 0 ){
                        p2w = new Player2win;
                        p2w->show();
                    }
                }
            }
            break;
        case Qt::Key_E:
                on_player1 = false;
            break;
        /*玩家2*/
        case Qt::Key_Up:
            ui->label_player2->move(ui->label_player2->x(), ui->label_player2->y() - 3);
            ui->progressBar_player2->move(ui->progressBar_player2->x() , ui->progressBar_player2->y()- 3);
            break;
        case Qt::Key_Left:
            ui->label_player2->move(ui->label_player2->x() - 3, ui->label_player2->y());
            ui->progressBar_player2->move(ui->progressBar_player2->x()- 3, ui->progressBar_player2->y() );
            break;
        case Qt::Key_Down:
            ui->label_player2->move(ui->label_player2->x(), ui->label_player2->y() + 3);
            ui->progressBar_player2->move(ui->progressBar_player2->x(), ui->progressBar_player2->y() + 3);
            break;
        case Qt::Key_Right:
            ui->label_player2->move(ui->label_player2->x() + 3, ui->label_player2->y());
            ui->progressBar_player2->move(ui->progressBar_player2->x() + 3, ui->progressBar_player2->y());
            break;
        case Qt::Key_1:
            if((qPow(ui->label_player1->x()-ui->label_player2->x(),2)+qPow(ui->label_player1->y()-ui->label_player2->y(),2))<=2000) //攻击
            {
                if(on_player2==false)
                {
                    hp_player1-=5;
                    ui->progressBar_player1->setValue(hp_player1);
                    on_player2 = true;
                    if(hp_player1 == 0 ){
                        p1w = new Player1win;
                        p1w->show();
                    }

                }
            }
            break;
        case Qt::Key_2:
                on_player2 = false;
            break;
        default:
            break;
        }
    }
}


