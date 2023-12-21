#include "editrow.h"

EditRow::EditRow(QWidget *parent)
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

QLineEdit* EditRow::getDescription() {
    return description;
}

QLineEdit* EditRow::getReps() {
    return reps;
}

QLineEdit* EditRow::getUnits() {
    return units;
}

void EditRow::setDescription(QString description) {
    this->description->setText(description);
}

void EditRow::setReps(int reps) {
    this->reps->setText(QString::number(reps));
}

void EditRow::setUnits(QString units) {
    this->units->setText(units);
}
