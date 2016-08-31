#ifndef CROSS_H
#define CROSS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPaintEvent>

/// A Cross on the board
class Cross : public QWidget
{
    Q_OBJECT
public:
    explicit Cross(int _row, int _column, QWidget *parent);

    void drawPiece(bool color) { hasPiece = true, pieceColor = color; update(); }
    void reset() { hasPiece = false; update(); }

signals:
    void onClick(int _row, int _column);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;

private:
    int row, column;

    bool hasPiece, pieceColor;
};

#endif // CROSS_H
