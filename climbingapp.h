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
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>

#include "workoutrow.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ClimbingApp; }
QT_END_NAMESPACE

class ClimbingApp : public QMainWindow
{
    Q_OBJECT

public:
    ClimbingApp(QWidget *parent = nullptr);
    ~ClimbingApp();

    void setWorkoutList(std::vector<WorkoutData> workoutList);

    QString toString();

    void printData();

    bool isInt(QString str);

private slots:
    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionDebug_triggered();

    void on_actionAdd_Row_triggered();

    void on_actionDelete_Row_triggered();

private:
    Ui::ClimbingApp *ui;

    // Integer value is for order of workout, all the data is the rest of the data.
    // QMap<int, WorkoutData> workoutList;
    // WorkoutData workoutList;
    std::vector<WorkoutData> workoutList;

    std::vector<WorkoutRow*> listOfWorkoutRows;

    // The vertical layout that stores the box, and more
    QVBoxLayout* mainVLayout;

    // The main box that stores all the rows
    QGroupBox* mainBox;

    // The vertical layout that is in the box
    QVBoxLayout* boxVLayout;


};
#endif // CLIMBINGAPP_H
