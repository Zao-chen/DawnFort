#include "game.h"
#include "ui_game.h"
#include <QDebug>
#include <QtMath>
#include <player1win.h>
#include <player2win.h>
#include <QTimer>
#include <QTime>


bool on_player1=false;
bool on_player2=false;


game::game(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::game)
{
    ui->setupUi(this);
    keyRespondTimer = new QTimer(this);
    connect(keyRespondTimer, &QTimer::timeout, this, &game::slowTimeOut); //按键信号

    this->startTimer(40);

}

//重写定时器事件
void game::timerEvent(QTimerEvent *e)
{
    ui->progressBar_go->setValue(ui->progressBar_go->value()+2);
    ui->progressBar_go_2->setValue(ui->progressBar_go_2->value()+2); //蓄力条回复
    ui->talk_1->setText("Player1");
    ui->talk_2->setText("Player2");


    /*子弹射击*/
    //Player1
    ui->label_player1_zidan->move(ui->label_player1_zidan->x()+70,ui->label_player1_zidan->y());
    if((qPow(ui->label_player1_zidan->x()-ui->label_player2->x(),2)+qPow(ui->label_player1_zidan->y()-20-ui->label_player2->y(),2))<=4000) //攻击
    {
        ui->talk_2->setText("受伤！");
        hp_player2-=10;
        ui->progressBar_player2->setValue(hp_player2);
        on_player1 = true;
        if(hp_player2 == 0 ){
            p1w = new Player1win;
            p1w->show();
        }
    }
    // Player 2
    ui->label_player2_zidan->move(ui->label_player2_zidan->x()-70,ui->label_player2_zidan->y());
    if((qPow(ui->label_player2_zidan->x()-ui->label_player1->x(),2)+qPow(ui->label_player2_zidan->y()-ui->label_player1->y(),2))<=4000) //攻击
    {
        ui->talk_2->setText("受伤！");
        hp_player1-=10;
        ui->progressBar_player1->setValue(hp_player1);
        on_player2 = true;
        if(hp_player1 == 0 ){
            p2w = new Player2win;
            p2w->show();
        }
    }
}


game::~game()
{
    delete ui;
}



void game::keyPressEvent(QKeyEvent *event){
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的按下,就将key值加入容器
    {
        keys.append(event->key());

    }
    if(!keyRespondTimer->isActive()) //如果定时器不在运行，就启动一下
        keyRespondTimer->start(4);
}
void game::keyReleaseEvent(QKeyEvent *event){
    if(!event->isAutoRepeat())  //判断如果不是长按时自动触发的释放,就将key值从容器中删除
    {
        keys.removeAll(event->key());
    }
    if(keys.isEmpty()) //容器空了，关闭定时器
        keyRespondTimer->stop();
}


void game::slowTimeOut(){ //输入按键
    ui->label->setText(QString::number((qPow(ui->label_player1->x()-ui->label_player2->x(),2)+qPow(ui->label_player1->y()-ui->label_player2->y(),2))));
    foreach (int key, keys) {
        //玩家定位
        int p1_x = ui->label_player1->x();
        int p1_y = ui->label_player1->y();
        int p2_x = ui->label_player2->x();
        int p2_y = ui->label_player2->y();
        int speed = 1; //可控量：速度
        switch (key) {
        /*玩家1*/
        case Qt::Key_W:
            if(p1_y>0)
            {
                ui->label_player1->move(p1_x, p1_y - speed);
                ui->progressBar_player1->move(p1_x, p1_y - speed);
                ui->progressBar_go->move(p1_x, p1_y-30 - speed);
                ui->talk_1->move(p1_x, p1_y-45- speed);
            }
            break;
        case Qt::Key_A:
            if(p1_x>0)
            {
                ui->label_player1->move(p1_x - speed, p1_y);
                ui->progressBar_player1->move(p1_x- speed, p1_y );
                ui->progressBar_go->move(p1_x-3, p1_y-30);
                ui->talk_1->move(p1_x-3, p1_y-45);
            }
            break;
        case Qt::Key_S:
            if(p1_y<this->size().height()-10)
            {
                ui->label_player1->move(p1_x, p1_y + speed);
                ui->progressBar_player1->move(p1_x, p1_y + speed);
                ui->progressBar_go->move(p1_x, p1_y-30 + speed);
                ui->talk_1->move(p1_x, p1_y-45+ speed);
            }
            break;
        case Qt::Key_D:
            if(p1_x<this->size().width()/2-50)
            {
                ui->label_player1->move(p1_x + speed, p1_y);
                ui->progressBar_player1->move(p1_x + speed, p1_y);
                ui->progressBar_go->move(p1_x+3, p1_y-30);
                ui->talk_1->move(p1_x+3, p1_y-45);
            }
            break;
        case Qt::Key_Space: //攻击
            if(ui->progressBar_go->value()>=100)
            {
                ui->label_player1_zidan->move(p1_x+20,p1_y+40);
                ui->progressBar_go->setValue(0); //重置条子
                ui->talk_1->setText("攻击！");
            }
            break;
        /*玩家2*/
        case Qt::Key_Up:
            if(p2_y>0)
            {
                ui->label_player2->move(p2_x, p2_y - speed);
                ui->progressBar_player2->move(p2_x , p2_y- speed);
                ui->progressBar_go_2->move(p2_x , p2_y-30- speed);
                ui->talk_2->move(p2_x, p2_y-45- speed);
            }
            break;
        case Qt::Key_Left:
            if(p2_x>this->size().width()/2+50)
            {
                ui->label_player2->move(p2_x - speed, p2_y);
                ui->progressBar_player2->move(p2_x- speed, p2_y );
                ui->progressBar_go_2->move(p2_x -3, p2_y-30);
                ui->talk_2->move(p2_x-3, p2_y-45);
            }
            break;
        case Qt::Key_Down:
            if(p2_y<this->size().height()-10)
            {
                ui->label_player2->move(p2_x, p2_y + speed);
                ui->progressBar_player2->move(p2_x, p2_y + speed);
                ui->progressBar_go_2->move(p2_x , p2_y-30+ speed);
                ui->talk_2->move(p2_x, p2_y-45+ speed);
            }
            break;
        case Qt::Key_Right:
            if(p2_x<this->size().width()-10)
            {
                ui->label_player2->move(p2_x + speed, p2_y);
                ui->progressBar_player2->move(p2_x + speed, p2_y);
                ui->progressBar_go_2->move(p2_x+3 , p2_y-30);
                ui->talk_2->move(p2_x+3, p2_y-45);
            }
            break;
        case Qt::Key_0: //攻击

            if(ui->progressBar_go_2->value()>=100)
            {
                ui->talk_2->setText("攻击！");
                ui->progressBar_go_2->setValue(0); //重置条子
                ui->label_player2_zidan->move(p2_x+20,p2_y+40);
            }
            break;
        default:
            break;
        }
    }
}


