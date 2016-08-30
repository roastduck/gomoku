#include <ctime>
#include <cstdlib>
#include <QApplication>
#include "gomoku.h"

int main(int argc, char *argv[])
{
    srand(time(0));

    QApplication a(argc, argv);
    Gomoku w;
    w.show();

    return a.exec();
}
