#include "climbingapp.h"

#include <QApplication>
#include <QVBoxLayout>
#include <QGroupBox>
#include <QPlainTextEdit>
#include <QLineEdit>
#include <QPushButton>
#include <QLabel>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClimbingApp w;

    w.setMinimumSize(1000, 1000);

    w.show();

    return a.exec();
}
