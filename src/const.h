#ifndef CONST_H
#define CONST_H

#include <QPair>
#include <QString>
#include <QJsonValue>

/// TCP port
const int PORT = 8388;

const int BOARD_SIZE = 15;

typedef QPair<QString, QJsonValue> JsonKeyValue;

#endif // CONST_H
