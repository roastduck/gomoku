#ifndef IPINPUT_H
#define IPINPUT_H

#include <QDebug>
#include <QString>
#include <QObject>
#include <QDialog>

namespace Ui {
class IpInput;
}

class IpInput : public QDialog
{
    Q_OBJECT

public:
    explicit IpInput(QWidget *parent = 0);
    ~IpInput();

    static QString getText();

private slots:
    void on_button0_clicked(bool checked);
    void on_button1_clicked(bool checked);
    void on_button2_clicked(bool checked);
    void on_button3_clicked(bool checked);
    void on_button4_clicked(bool checked);
    void on_button5_clicked(bool checked);
    void on_button6_clicked(bool checked);
    void on_button7_clicked(bool checked);
    void on_button8_clicked(bool checked);
    void on_button9_clicked(bool checked);
    void on_buttonDot_clicked(bool checked);

private:
    Ui::IpInput *ui;
};

class Getter : public QObject
{
    Q_OBJECT
public:
    Getter() : text("127.0.0.1") {}
    QString text;

public slots:
    void getText(QString _text)
    {
        text = _text;
    }
};

#endif // IPINPUT_H
