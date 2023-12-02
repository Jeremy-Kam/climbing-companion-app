#include "workoutrow.h"

WorkoutRow::WorkoutRow(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *workoutElementLayout = new QHBoxLayout(this);

    description = new QLineEdit();
    reps = new QLineEdit();
    units = new QLineEdit();

    workoutElementLayout->addWidget(description);
    workoutElementLayout->addWidget(reps);
    workoutElementLayout->addWidget(units);

    this->setLayout(workoutElementLayout);

}

QLineEdit* WorkoutRow::getDescription() {
    return description;
}

QLineEdit* WorkoutRow::getReps() {
    return reps;
}

QLineEdit* WorkoutRow::getUnits() {
    return units;
}

void WorkoutRow::setDescription(QString description) {
    this->description->setText(description);
}

void WorkoutRow::setReps(int reps) {
    this->reps->setText(QString::number(reps));
}

void WorkoutRow::setUnits(QString units) {
    this->units->setText(units);
}
