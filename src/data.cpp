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
    disconnect(this, SLOT(drawOutputBlack(int,int)));
    disconnect(this, SLOT(drawOutputWhite(int,int)));
}

void Data::drawInput(int row, int column)
{
    if (localColor != currentColor || ! localReady || ! remoteReady) return;
    currentColor = ! currentColor;
    emit local->draw(row, column);
    remote->send("draw", { JsonKeyValue("row", row), JsonKeyValue("column", column)});
}

void Data::sendRestart()
{
    remote->send("restart");
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
    QMessageBox::information(0, "Color", color ? "You use white" : "You use black");
    connect(color ? remote : local, SIGNAL(draw(int,int)), this, SLOT(drawOutputBlack(int,int)));
    connect(color ? local : remote, SIGNAL(draw(int,int)), this, SLOT(drawOutputWhite(int,int)));
}

void Data::drawOutputWhite(int row, int column)
{
    qDebug() << " -- drew white " << row << " , " << column;
    currentColor = 0;
    emit drawOutput(row, column, 1);
}

void Data::drawOutputBlack(int row, int column)
{
    qDebug() << " -- drew black " << row << " , " << column;
    currentColor = 1;
    emit drawOutput(row, column, 0);
}
