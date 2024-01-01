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

    editDate = new QDateTimeEdit();
    editDate->setFixedHeight(rowHeight);
    editDate->setFixedWidth(dateEditWidth);

    workoutElementLayout->addWidget(description);
    workoutElementLayout->addWidget(reps);
    workoutElementLayout->addWidget(units);
    workoutElementLayout->addWidget(editDate);

    this->setLayout(workoutElementLayout);
}

EditRow::~EditRow() {

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

QDateTimeEdit* EditRow::getDate() {
    return editDate;
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
