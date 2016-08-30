#ifndef INPUT_H
#define INPUT_H

#include <QObject>

/// Base class for user input from local or remote
class Input : public QObject
{
    Q_OBJECT
public:
    explicit Input(QObject *parent);

signals:
    /// draw a piece
    void draw(int row, int column);
};

#endif // INPUT_H
