#include <QDebug>
#include <QLineEdit>
#include <QMessageBox>
#include <QGridLayout>
#include <QInputDialog>
#include "data.h"
#include "board.h"
#include "cross.h"
#include "input.h"
#include "const.h"
#include "gomoku.h"
#include "ui_gomoku.h"
#include "remoteinput.h"
#include "serverdialog.h"

Gomoku::Gomoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gomoku)
{
    ui->setupUi(this);

    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
        {
            Cross *cross = new Cross(i, j, ui->boardWidget);
            connect(cross, SIGNAL(onClick(int,int)), Data::getInst(), SLOT(drawInput(int,int)));
            dynamic_cast<QGridLayout*>(ui->boardWidget->layout())->addWidget(cross, i, j);
        }

    connect(Data::getInst()->remote, SIGNAL(connectError()), this, SLOT(promptConnectError()));
    connect(Data::getInst()->remote, SIGNAL(hello()), this, SLOT(connected()));
    connect(Data::getInst(), SIGNAL(drawOutput(int,int,bool)), this, SLOT(drawPiece(int,int,bool)));

    connect(ui->restartButton, SIGNAL(clicked(bool)), this, SLOT(restart()));
    connect(ui->restartButton, SIGNAL(clicked(bool)), Data::getInst(), SLOT(sendRestart()));
    connect(Data::getInst()->remote, SIGNAL(requestRestart()), this, SLOT(restart()));

    connect(Data::getInst(), SIGNAL(win(bool)), this, SLOT(promptWin(bool)));
}

Gomoku::~Gomoku()
{
    delete ui;
}

void Gomoku::promptConnectError()
{
    QMessageBox::warning(this, tr("Error"), tr("Disconnected"), QMessageBox::Close);
    ui->clientButton->setDisabled(false);
    ui->serverButton->setDisabled(false);
    ui->readyButton->setDisabled(true);
    ui->restartButton->setDisabled(true);
    ui->clientButton->setText(tr("Connect to Server"));
    ui->statusLabel->setText(tr("Not connected"));
}

void Gomoku::promptWin(bool color)
{
    QMessageBox::warning(this, tr("Game Ended"), color ? tr("White wins") : tr("Black wins"), QMessageBox::Close);
}

void Gomoku::connected()
{
    ui->clientButton->setDisabled(true);
    ui->serverButton->setDisabled(true);
    ui->readyButton->setDisabled(false);
    ui->restartButton->setDisabled(false);
    ui->statusLabel->setText(tr("Connected"));
    restart();
}

void Gomoku::restart()
{
    ui->readyButton->setDisabled(false);
    Data::getInst()->reset();
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            dynamic_cast<Cross*>(dynamic_cast<QGridLayout*>(ui->boardWidget->layout())->itemAtPosition(i, j)->widget())->reset();
}

void Gomoku::drawPiece(int row, int column, bool color)
{
    qDebug() << " -- draw (" << row << " , " << column << ") color: " << color;
    Cross *cross = dynamic_cast<Cross*>(dynamic_cast<QGridLayout*>(ui->boardWidget->layout())->itemAtPosition(row, column)->widget());
    cross->drawPiece(color);
}

void Gomoku::on_serverButton_clicked(bool)
{
    ServerDialog *dialog = new ServerDialog;
    dialog->show();
    dialog->setAttribute(Qt::WA_DeleteOnClose);
}

void Gomoku::on_clientButton_clicked(bool)
{
    QString ip = QInputDialog::getText(this, tr("Connect to Server"), tr("Server address:"), QLineEdit::Normal, "127.0.0.1");
    emit Data::getInst()->remote->connectToServer(ip);
    ui->clientButton->setText(tr("Reconnect"));
    ui->statusLabel->setText(tr("Connecting..."));
}

void Gomoku::on_disconnectButton_clicked(bool)
{
    emit Data::getInst()->remote->reset();
}

void Gomoku::on_readyButton_clicked(bool)
{
    Data::getInst()->setLocalReady();
    ui->readyButton->setDisabled(true);
}

void Gomoku::on_dangButton_pressed()
{
    Data::getInst()->showDangerous = true;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            dynamic_cast<QGridLayout*>(ui->boardWidget->layout())->itemAtPosition(i, j)->widget()->update();
}

void Gomoku::on_dangButton_released()
{
    Data::getInst()->showDangerous = false;
    for (int i = 0; i < BOARD_SIZE; i++)
        for (int j = 0; j < BOARD_SIZE; j++)
            dynamic_cast<QGridLayout*>(ui->boardWidget->layout())->itemAtPosition(i, j)->widget()->update();
}
