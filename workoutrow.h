#ifndef WORKOUTROW_H
#define WORKOUTROW_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QMap>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>

class WorkoutRow : public QWidget
{
    Q_OBJECT
public:
    explicit WorkoutRow(QWidget *parent = nullptr);

    QLineEdit* getDescription();
    QLineEdit* getReps();
    QLineEdit* getUnits();

    void setDescription(QString description);
    void setReps(int reps);
    void setUnits(QString reps);

signals:



private:
    QGroupBox mainBox;

    QLineEdit* description;
    QLineEdit* reps;
    QLineEdit* units;

    QPushButton* editButton;
    QPushButton* deleteButton;

    int rowHeight = 30;
    int repsUnitLabelWidth = 100;
    int buttonWidth = 30;

};

#endif // WORKOUTROW_H
