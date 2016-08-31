#ifndef BOARD_H
#define BOARD_H

#include <QObject>
#include "const.h"

/// Gomoku board
class Board : public QObject
{
    Q_OBJECT
public:
    explicit Board(QObject *parent = 0);

    void reset();

    void draw(int row, int column, bool color);

signals:
    void win(bool color);

private:
    bool inBoard(int row, int column);

    const int walk[8][2] = {{-1,0}, {-1,1}, {0,1}, {1,1}, {1,0}, {1,-1}, {0,-1}, {-1,-1}};

    int board[BOARD_SIZE][BOARD_SIZE];
};

#endif // BOARD_H
