#include "workoutrow.h"

WorkoutRow::WorkoutRow(QWidget *parent, int index)
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

    editButton = new QPushButton();
    editButton->setFixedHeight(rowHeight);
    editButton->setFixedWidth(buttonWidth);

    deleteButton = new QPushButton();
    deleteButton->setFixedHeight(rowHeight);
    deleteButton->setFixedWidth(buttonWidth);

    workoutElementLayout->addWidget(description);
    workoutElementLayout->addWidget(reps);
    workoutElementLayout->addWidget(units);

    workoutElementLayout->addWidget(editButton);
    workoutElementLayout->addWidget(deleteButton);

    this->setLayout(workoutElementLayout);

    this->index = index;

    QObject::connect(editButton, &QPushButton::clicked, this, &WorkoutRow::editButtonPressed);
    QObject::connect(deleteButton, &QPushButton::clicked, this, &WorkoutRow::deleteButtonPressed);
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

void WorkoutRow::editButtonPressed() {
    qDebug() << "Edit Button Pressed: " + QString::number(index);
    emit openEditWindow(index);
}

void WorkoutRow::deleteButtonPressed() {
    qDebug() << "Delete Button Pressed: " + QString::number(index);
    emit deleteRow(index);
}

void WorkoutRow::setIndex(int index) {
    this->index = index;
}
