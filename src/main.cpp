#include <ctime>
#include <cstdlib>
#include <QApplication>
#include "data.h"
#include "gomoku.h"

int main(int argc, char *argv[])
{
    srand(time(0));

    QApplication a(argc, argv);
    Gomoku w;
    w.show();

    int ret = a.exec();

    Data::delInst();

    return ret;
}
