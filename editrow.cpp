#include "editrow.h"

EditRow::EditRow(QWidget *parent, QString description, int reps, QString units, QDateTime date)
    : QWidget{parent}
{
    QHBoxLayout *workoutElementLayout = new QHBoxLayout(this);

    this->description = new QLineEdit();
    this->description->setFixedHeight(rowHeight);
    this->description->setText(description);

    this->reps = new QLineEdit();
    this->reps->setFixedHeight(rowHeight);
    this->reps->setFixedWidth(repsUnitLabelWidth);
    this->reps->setText(QString::number(reps));

    this->units = new QLineEdit();
    this->units->setFixedHeight(rowHeight);
    this->units->setFixedWidth(repsUnitLabelWidth);
    this->units->setText(units);

    this->editDate = new QDateTimeEdit();
    this->editDate->setFixedHeight(rowHeight);
    this->editDate->setFixedWidth(dateWidth);
    this->editDate->setDateTime(date);

    this->editDate->setCalendarPopup(true);

    workoutElementLayout->addWidget(this->description);
    workoutElementLayout->addWidget(this->reps);
    workoutElementLayout->addWidget(this->units);
    workoutElementLayout->addWidget(this->editDate);

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

void EditRow::setDate(QDateTime date) {
    editDate->setDateTime(date);
}
