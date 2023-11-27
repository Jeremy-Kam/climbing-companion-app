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

class WorkoutRow : public QWidget
{
    Q_OBJECT
public:
    explicit WorkoutRow(QWidget *parent = nullptr);

signals:



private:
    QGroupBox mainBox;
    QVBoxLayout boxVLayout;

};

#endif // WORKOUTROW_H
