#include <QMessageBox>
#include "data.h"
#include "remoteinput.h"
#include "serverdialog.h"
#include "ui_serverdialog.h"

ServerDialog::ServerDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ServerDialog)
{
    ui->setupUi(this);
    ui->cancelButton->hide();

    connect(Data::getInst()->remote, SIGNAL(serverError()), this, SLOT(promptServerError()));
    connect(Data::getInst()->remote, SIGNAL(newClientList(const QList<QString> &)), this, SLOT(newClientList(const QList<QString> &)));
}

ServerDialog::~ServerDialog()
{
    delete ui;
}

void ServerDialog::promptServerError()
{
    QMessageBox::warning(this, tr("Setup failed"), tr("Invalid address."), QMessageBox::Close);
}

void ServerDialog::newClientList(const QList<QString> &list)
{
    ui->listWidget->clear();
    for (int i = 0; i < list.size(); i++)
        ui->listWidget->addItem(list[i]);
}

void ServerDialog::on_setupButton_clicked(bool)
{
    emit Data::getInst()->remote->setupServer(ui->ipInput->text());
    ui->setupButton->hide();
    ui->cancelButton->show();
}

void ServerDialog::on_listWidget_itemActivated(QListWidgetItem *item)
{
    emit Data::getInst()->remote->acceptClient(ui->listWidget->row(item));
    deleteLater();
}

void ServerDialog::on_cancelButton_clicked(bool)
{
    emit Data::getInst()->remote->reset();
    ui->setupButton->show();
    ui->cancelButton->hide();
}
