#include <algorithm>
#include <QPen>
#include <QBrush>
#include <QColor>
#include <QPixmap>
#include <QPainter>
#include "data.h"
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

    if (((row == 3 || row == 11) && (column == 3 || column == 11)) || (row == 7 && column == 7))
    {
        p.setPen(QPen(Qt::black, 7));
        p.drawLine(l/2, l/2, l/2, l/2);
    }

    if (hasPiece)
    {
        p.setPen(Qt::NoPen);
        p.setBrush(pieceColor ? Qt::white : Qt::black);
        p.drawEllipse(l * 0.1, l * 0.1, l * 0.8, l * 0.8);
    }

    if (Data::getInst()->showDangerous && Data::getInst()->board.isDangerous(row, column, Data::getInst()->getLocalColor()))
    {
        qDebug() << " -- position" << row << "," << column << "is dangerous";
        QPixmap pixmap(":/bomb.ico");
        p.drawPixmap(0, 0, l, l, pixmap);
    }
}

void Cross::mousePressEvent(QMouseEvent *event)
{
    if (! hasPiece)
        emit onClick(row, column);
    QWidget::mousePressEvent(event);
}
