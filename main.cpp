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

    /*
    ClimbingApp window;
    QWidget *widget = new QWidget(&window);
    QVBoxLayout *layout = new QVBoxLayout(widget);

    window.setCentralWidget(widget);
    widget->setLayout(layout);

    QGroupBox *box = new QGroupBox("Dishes:", widget);
    QVBoxLayout *boxLayout = new QVBoxLayout(box);

    layout->addWidget(box);

    // Column name
    QWidget* columnNameWidget = new QWidget(box);
    boxLayout->addWidget(columnNameWidget);

    QHBoxLayout *columnNameLayout = new QHBoxLayout(columnNameWidget);
    columnNameLayout->addWidget(new QLabel("Description", columnNameWidget));
    columnNameLayout->addWidget(new QLabel("Reps", columnNameWidget));
    columnNameLayout->addWidget(new QLabel("Units", columnNameWidget));

    // Row of workout
    QWidget* workoutElementWidget = new QWidget(box);
    boxLayout->addWidget(workoutElementWidget);

    QHBoxLayout *workoutElementLayout = new QHBoxLayout(workoutElementWidget);
    workoutElementLayout->addWidget(new QLineEdit(workoutElementWidget));
    workoutElementLayout->addWidget(new QLineEdit(workoutElementWidget));
    workoutElementLayout->addWidget(new QLineEdit(workoutElementWidget));

    window.show();

    */

    ClimbingApp w;
    w.show();

    return a.exec();
}
