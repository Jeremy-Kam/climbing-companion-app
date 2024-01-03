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
#include <QtCharts>
#include <QtCharts/QLegend>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QLineSeries>
#include <QtCharts/QCategoryAxis>
#include <QScrollArea>
#include <QSpacerItem>

#include "workoutrow.h"
#include "editrow.h"
#include "editwindow.h"

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

    void createCharts();
    void updateCharts();

private slots:
    void on_actionSave_triggered();

    void on_actionExit_triggered();

    void on_actionDebug_triggered();

    void on_actionAdd_Row_triggered();

    void on_actionDelete_Row_triggered();

    void openEditWindow(int index);

    void deleteRowAtIndex(int index);

    void updateRowAtIndex(int index);

private:
    Ui::ClimbingApp *ui;

    // Integer value is for order of workout, all the data is the rest of the data.
    // QMap<int, WorkoutData> workoutList;
    // WorkoutData workoutList;
    std::vector<WorkoutData> workoutList;

    std::vector<WorkoutRow*> listOfWorkoutRows;

    std::vector<QChartView*> listOfChartViews;

    // The vertical layout that stores the box, and more
    QVBoxLayout* mainVLayout;

    // The main box that stores all the rows
    QGroupBox* mainBox;

    // The vertical layout that is in the box
    QVBoxLayout* boxVLayout;

    // Vertical layout that stores the graphs
    QVBoxLayout* graphVLayout;

    std::vector<unsigned int> graphColors = {0x076CE8, 0x00E6D2, 0xBF6000, 0xFF6C23, 0x334A66};

    EditWindow* currentEditWindow;

    int labelHeight = 30;
    int repsUnitsWidth = 100;

};
#endif // CLIMBINGAPP_H
