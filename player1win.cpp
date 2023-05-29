#include "player1win.h"
#include "ui_player1win.h"

Player1win::Player1win(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Player1win)
{
    ui->setupUi(this);
}

Player1win::~Player1win()
{
    delete ui;
}
