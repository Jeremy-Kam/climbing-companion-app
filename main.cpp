#include "climbingapp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClimbingApp w;
    w.show();
    return a.exec();
}
