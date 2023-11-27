#include "workoutrow.h"

WorkoutRow::WorkoutRow(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *workoutElementLayout = new QHBoxLayout(this);
    workoutElementLayout->addWidget(new QLineEdit());
    workoutElementLayout->addWidget(new QLineEdit());
    workoutElementLayout->addWidget(new QLineEdit());

    this->setLayout(workoutElementLayout);

}
