#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QWidget>
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

#include "editrow.h"
#include "rowdata.h"
#include "workoutdata.h"


class EditWindow : public QWidget
{
    Q_OBJECT
public:
    explicit EditWindow(QWidget *parent, WorkoutData data, int index);

    ~EditWindow();

    //QMap<QDateTime, RowData> getNewData();

signals:
    //void dataSavedForRow(int index);

private slots:
    //void saveData();

private:
    std::vector<EditRow*> editRows;
    int index;

    QPushButton* saveButton;

    int labelHeight = 30;
    int repsUnitsWidth = 100;
    int dateEditWidth = 150;

};

#endif // EDITWINDOW_H
