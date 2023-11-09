#ifndef CLIMBINGAPP_H
#define CLIMBINGAPP_H

#include "workoutdata.h"
#include <QMainWindow>
#include <QDateTime>
#include <QMap>
#include <QVector>
#include <QPair>

#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QMap>

QT_BEGIN_NAMESPACE
namespace Ui { class ClimbingApp; }
QT_END_NAMESPACE

class ClimbingApp : public QMainWindow
{
    Q_OBJECT

public:
    ClimbingApp(QWidget *parent = nullptr);
    ~ClimbingApp();

private:
    Ui::ClimbingApp *ui;

    // Integer value is for order of workout, all the data is the rest of the data.
    // QMap<int, WorkoutData> workoutList;
    WorkoutData workoutList;


};
#endif // CLIMBINGAPP_H
