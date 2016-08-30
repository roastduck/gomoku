#ifndef DATA_H
#define DATA_H

#include <QObject>
#include "input.h"
#include "remoteinput.h"

/// Manages all data
class Data : public QObject
{
    Q_OBJECT
public:
    Data(const Data &) = delete;

    /// Get singleton instance
    static Data *getInst();

    /// local player
    Input *local;
    /// remote player
    RemoteInput *remote;

private:
    explicit Data(QObject *parent = 0);

    static Data *instance;
};

#endif // DATA_H
