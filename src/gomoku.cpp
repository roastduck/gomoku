#include <QLineEdit>
#include <QMessageBox>
#include <QInputDialog>
#include "data.h"
#include "input.h"
#include "gomoku.h"
#include "ui_gomoku.h"
#include "remoteinput.h"
#include "serverdialog.h"

Gomoku::Gomoku(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Gomoku)
{
    ui->setupUi(this);

    connect(Data::getInst()->remote, SIGNAL(connectError()), this, SLOT(promptConnectError()));
    connect(Data::getInst()->remote, SIGNAL(hello()), this, SLOT(connected()));
}

Gomoku::~Gomoku()
{
    delete ui;
}

void Gomoku::promptConnectError()
{
    QMessageBox::warning(this, tr("Error"), tr("Connection failed"), QMessageBox::Close);
    ui->clientButton->setDisabled(false);
    ui->serverButton->setDisabled(false);
    ui->clientButton->setText(tr("Connect to Server"));
    ui->statusLabel->setText(tr("Not connected"));
}

void Gomoku::connected()
{
    ui->clientButton->setDisabled(true);
    ui->serverButton->setDisabled(true);
    ui->statusLabel->setText(tr("Connected"));
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
