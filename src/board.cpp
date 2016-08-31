#include <cstring>
#include "board.h"

Board::Board(QObject *parent) : QObject(parent)
{
    reset();
}

void Board::reset()
{
    memset(board, 255, sizeof board);
}

void Board::draw(int row, int column, bool color)
{
    Q_ASSERT(inBoard(row, column));
    board[row][column] = color;

    for (int k = 0; k < 4; k++)
    {
        int cnt(1);
        for (int x=row+walk[k][0], y=column+walk[k][1]; inBoard(x,y) && board[x][y]==color; x+=walk[k][0], y+=walk[k][1])
            cnt++;
        for (int x=row-walk[k][0], y=column-walk[k][1]; inBoard(x,y) && board[x][y]==color; x-=walk[k][0], y-=walk[k][1])
            cnt++;
        if (cnt >= 5)
        {
            emit win(color);
            break;
        }
    }
}

bool Board::inBoard(int row, int column)
{
    return row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE;
}

bool Board::isDangerous(int row, int column, bool color)
{
    Q_ASSERT(inBoard(row, column));
    if (~board[row][column]) return false;
    int cnt1(0);
    for (int k = 0; k < 4; k++)
    {
        int tot(1); // avalible space
        for (int x=row+walk[k][0], y=column+walk[k][1]; inBoard(x,y) && board[x][y]!=color; x+=walk[k][0], y+=walk[k][1])
            tot++;
        for (int x=row-walk[k][0], y=column-walk[k][1]; inBoard(x,y) && board[x][y]!=color; x-=walk[k][0], y-=walk[k][1])
            tot++;
        if (tot < 5) continue;
        int cnt2(0);
        if (board[row+walk[k][0]][column+walk[k][1]] == !color)
            for (int x=row+walk[k][0], y=column+walk[k][1]; inBoard(x,y) && board[x][y]!=color; x+=walk[k][0], y+=walk[k][1])
            {
                cnt2++;
                if (!~board[x][y]) break;
            }
        if (board[row-walk[k][0]][column-walk[k][1]] == !color)
            for (int x=row-walk[k][0], y=column-walk[k][1]; inBoard(x,y) && board[x][y]!=color; x-=walk[k][0], y-=walk[k][1])
            {
                cnt2++;
                if (!~board[x][y]) break;
            }
        if (cnt2 >= 3) cnt1++;
    }
    return cnt1 >= 2;
}
