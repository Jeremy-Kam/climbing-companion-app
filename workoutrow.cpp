#include "workoutrow.h"

WorkoutRow::WorkoutRow(QWidget *parent)
    : QWidget{parent}
{
    QHBoxLayout *workoutElementLayout = new QHBoxLayout(this);

    description = new QLineEdit();
    description->setFixedHeight(rowHeight);

    reps = new QLineEdit();
    reps->setFixedHeight(rowHeight);
    reps->setFixedWidth(repsUnitLabelWidth);

    units = new QLineEdit();
    units->setFixedHeight(rowHeight);
    units->setFixedWidth(repsUnitLabelWidth);

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
