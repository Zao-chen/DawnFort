#include "player2win.h"
#include "ui_player2win.h"

Player2win::Player2win(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player2win)
{
    ui->setupUi(this);
}

Player2win::~Player2win()
{
    delete ui;
}
