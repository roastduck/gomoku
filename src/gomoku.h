#ifndef GOMOKU_H
#define GOMOKU_H

#include <QMainWindow>

namespace Ui {
class Gomoku;
}

/// Main window
class Gomoku : public QMainWindow
{
    Q_OBJECT

public:
    explicit Gomoku(QWidget *parent = 0);
    ~Gomoku();

private slots:
    void promptConnectError();
    void promptWin(bool color);
    void connected();
    /// clear board and reset color
    void restart();

    void drawPiece(int row, int column, bool color);

    void on_serverButton_clicked(bool checked);
    void on_clientButton_clicked(bool checked);
    void on_disconnectButton_clicked(bool checked);
    void on_readyButton_clicked(bool checked);

private:
    Ui::Gomoku *ui;
};

#endif // GOMOKU_H
