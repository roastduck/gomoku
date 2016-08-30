#include "data.h"

Data *Data::instance = 0;

Data::Data(QObject *parent) : QObject(parent)
{
    local = new Input(this);
    remote = new RemoteInput(this);
}

Data *Data::getInst()
{
    return instance ? instance : (instance = new Data());
}
