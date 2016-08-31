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

    /// set as ready to play
    void setLocalReady();
    void setRemoteReady();

    /// set local color and start game
    void startGame(bool color);

    /// clear board and reset color
    void reset();

    /// local player
    Input *local;
    /// remote player
    RemoteInput *remote;

signals:
    /// output draw to board
    void drawOutput(int row, int column, bool color);

public slots:
    /// input draw from user
    void drawInput(int row, int column);

    /// tell remote to restart
    void sendRestart();

private slots:
    void drawOutputBlack(int row, int column);
    void drawOutputWhite(int row, int column);

private:
    explicit Data(QObject *parent = 0);

    /// decide color and tell remote side
    void decideColor();

    bool localReady, remoteReady;
    bool localColor, currentColor;

    static Data *instance;
};

#endif // DATA_H
