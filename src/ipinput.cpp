#include <QDebug>
#include "ipinput.h"
#include "ui_ipinput.h"

IpInput::IpInput(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::IpInput)
{
    ui->setupUi(this);
}

IpInput::~IpInput()
{
    delete ui;
}

QString IpInput::getText()
{
    Getter getter;
    IpInput *input = new IpInput();
    connect(input->ui->lineEdit, SIGNAL(textChanged(QString)), &getter, SLOT(getText(QString)));
    if (input->exec())
        return getter.text;
    else
        return "";
}

void IpInput::on_button0_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + "0");
}

void IpInput::on_button1_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + "1");
}

void IpInput::on_button2_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + "2");
}

void IpInput::on_button3_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + "3");
}

void IpInput::on_button4_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + "4");
}

void IpInput::on_button5_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + "5");
}

void IpInput::on_button6_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + "6");
}

void IpInput::on_button7_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + "7");
}

void IpInput::on_button8_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + "8");
}

void IpInput::on_button9_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + "9");
}

void IpInput::on_buttonDot_clicked(bool)
{
    ui->lineEdit->setText(ui->lineEdit->text() + ".");
}
