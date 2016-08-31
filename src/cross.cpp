#include <algorithm>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPainter>
#include "cross.h"
#include "const.h"

Cross::Cross(int _row, int _column, QWidget *parent)
    : QWidget(parent), row(_row), column(_column), hasPiece(false) {}

void Cross::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
    int l(std::min(width(), height()));
    p.translate((width() - l) / 2, (height() - l) / 2);

    p.setPen(Qt::NoPen);
    p.setBrush(Qt::darkYellow);
    p.drawRect(0, 0, l, l);

    p.setPen(Qt::black);
    if (row > 0)
        p.drawLine(l/2, 0, l/2, l/2);
    if (row < BOARD_SIZE - 1)
        p.drawLine(l/2, l/2, l/2, l);
    if (column > 0)
        p.drawLine(0, l/2, l/2, l/2);
    if (column < BOARD_SIZE - 1)
        p.drawLine(l/2, l/2, l, l/2);

    if (hasPiece)
    {
        p.setPen(Qt::NoPen);
        p.setBrush(pieceColor ? Qt::white : Qt::black);
        p.drawEllipse(l * 0.1, l * 0.1, l * 0.8, l * 0.8);
    }
}

void Cross::mousePressEvent(QMouseEvent *event)
{
    emit onClick(row, column);
    QWidget::mousePressEvent(event);
}
