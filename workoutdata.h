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

    RowData getLatestRowData();

    void printAllData();

    QString toString();

    void openEditWindow();

private:
    // Use the most recent entry to display, but it stores all past edits.
    QMap<QDateTime, RowData> workoutHistory;

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


inline QDataStream& operator>>( QDataStream &in, WorkoutData& t )
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

inline QDataStream& operator>>( QDataStream &in, std::vector<WorkoutData>& t )
{
    int uniqueID;
    QDateTime tempDate;
    RowData tempRowData;
    QMap<QDateTime, RowData> tempWorkoutHistory;

    if(in.atEnd()) { // Empty list
        qDebug() << "Empty List";
        return in;
    }

    in >> tempDate;
    in >> tempRowData;

    uniqueID = tempRowData.getUniqueID();

    tempWorkoutHistory.insert(tempDate, tempRowData);

    while(!in.atEnd()) {
        in >> tempDate;
        in >> tempRowData;

        if(tempRowData.getUniqueID() != uniqueID) { // New element, reset everything and push element into it.
            WorkoutData tempWorkoutData;
            tempWorkoutData.setWorkoutHistory(tempWorkoutHistory);

            t.push_back(tempWorkoutData);
            uniqueID = tempRowData.getUniqueID();

            tempWorkoutHistory.clear();
        }
        tempWorkoutHistory.insert(tempDate, tempRowData);
    }

    WorkoutData tempWorkoutData;
    tempWorkoutData.setWorkoutHistory(tempWorkoutHistory);

    t.push_back(tempWorkoutData);

    return in;
}

#endif // WORKOUTDATA_H

