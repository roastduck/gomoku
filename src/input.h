#ifndef INPUT_H
#define INPUT_H

#include <QObject>

/// Base class for user input from local or remote
class Input : public QObject
{
    Q_OBJECT
public:
    explicit Input(QObject *parent);
};

#endif // INPUT_H
