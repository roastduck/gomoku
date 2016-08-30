#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include <QListWidgetItem>

namespace Ui {
class ServerDialog;
}

/// Dialog to setup a server
class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDialog(QWidget *parent = 0);
    ~ServerDialog();

private slots:
    void promptServerError();
    void newClientList(const QList<QString> &list);

    void on_setupButton_clicked(bool checked);
    void on_listWidget_itemActivated(QListWidgetItem *item);
    void on_cancelButton_clicked(bool checked);

private:
    Ui::ServerDialog *ui;
};

#endif // SERVERDIALOG_H
