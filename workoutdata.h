#ifndef WORKOUTDATA_H
#define WORKOUTDATA_H

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
#include <QString>
#include <QDataStream>
#include <QDateTime>
#include <QMap>

#include "rowdata.h"


class WorkoutData
{
public:



    WorkoutData();
    ~WorkoutData();

    QMap<QDateTime, RowData> getWorkoutHistory();
    void setWorkoutHistory(QMap<QDateTime, RowData> newData);
    void insertToWorkoutHistory(QDateTime date, RowData data);

    QString toString();

private:
    // Use the most recent entry to display, but it stores all past edits.
    QMap<QDateTime, RowData> workoutHistory;
    // rowData workoutHistory;

};

inline QDataStream& operator<<( QDataStream &out, WorkoutData& t )
{
    for(auto x: t.getWorkoutHistory().toStdMap()) {
        // out << x.first << "," << x.second << '\n';
        out << x.first;
        out << x.second;
    }

    // out << t.workoutHistory;

    return out;
}


inline QDataStream& operator>>( QDataStream &in, WorkoutData& t)
{
    QDateTime tempDate;
    RowData tempRowData;

    QMap<QDateTime, RowData> tempWorkoutHistory;

    while(!in.atEnd()) {
        in >> tempDate;
        in >> tempRowData;

        tempWorkoutHistory.insert(tempDate, tempRowData);
    }

    t.setWorkoutHistory(tempWorkoutHistory);

    return in;
}

#endif // WORKOUTDATA_H

