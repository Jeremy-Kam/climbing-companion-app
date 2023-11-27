#include "workoutrow.h"

WorkoutRow::WorkoutRow(QWidget *parent, QVBoxLayout* boxVLayout)
    : QWidget{parent}
{

    QVBoxLayout * layout = new QVBoxLayout;

    QWidget* workoutElementWidget = new QWidget(parent);
    boxVLayout->addWidget(workoutElementWidget);

    QHBoxLayout *workoutElementLayout = new QHBoxLayout(workoutElementWidget);
    workoutElementLayout->addWidget(new QLineEdit(workoutElementWidget));
    workoutElementLayout->addWidget(new QLineEdit(workoutElementWidget));
    workoutElementLayout->addWidget(new QLineEdit(workoutElementWidget));

    this->setLayout(layout);

}
