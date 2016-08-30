#include <cstdlib>
#include <QDebug>
#include <QMessageBox>
#include "data.h"
#include "const.h"
#include "input.h"
#include "remoteinput.h"

Data *Data::instance = 0;

Data::Data(QObject *parent) : QObject(parent)
{
    reset();
    local = new Input(this);
    remote = new RemoteInput(this);
    connect(local, SIGNAL(draw(int,int)), remote, SLOT(notify(int,int)));
}

Data *Data::getInst()
{
    return instance ? instance : (instance = new Data());
}

void Data::setLocalReady()
{
    localReady = true;
    remote->send("ready");
    decideColor();
}

void Data::setRemoteReady()
{
    remoteReady = true;
    decideColor();
}

void Data::reset()
{
    localReady = remoteReady = false;
    disconnect(0, 0, this, SLOT(drawOutputBlack(int,int)));
    disconnect(0, 0, this, SLOT(drawOutputWhite(int,int)));
}

void Data::drawInput(int row, int column)
{
    if (localColor != currentColor) return;
    emit local->draw(row, column);
    remote->send("draw", { JsonKeyValue("row", row), JsonKeyValue("column", column)});
}

void Data::decideColor()
{
    if (! remote->isServer() || ! localReady || ! remoteReady) return;
    bool localColor = rand() % 2;
    remote->send("startGame", { JsonKeyValue("color", ! localColor) });
    startGame(localColor);
}

void Data::startGame(bool color)
{
    qDebug() << " -- use color " << color;
    localColor = color;
    currentColor = 0;
    QMessageBox::information(this, "Color", color ? "You use white" : "You use black");
    connect(color ? remote : local, SIGNAL(draw(int,int)), this, SLOT(drawOutputBlack(int,int)));
    connect(color ? local : remote, SIGNAL(draw(int,int)), this, SLOT(drawOutputWhite(int,int)));
}

void Data::drawOutput(int row, int column, bool color)
{
    Q_ASSERT(currentColor == color);
    currentColor = ! currentColor;
}
