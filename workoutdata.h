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

    // Use the most recent entry to display, but it stores all past edits.
    // QMap<QDateTime, rowData> workoutHistory;
    rowData workoutHistory;

    WorkoutData();
    ~WorkoutData();

};

inline QDataStream& operator<<( QDataStream &out, WorkoutData& t )
{
    out << t.workoutHistory;

    return out;
}


inline QDataStream& operator>>( QDataStream &in, WorkoutData& t)
{
    in >> t.workoutHistory;

    return in;
}

#endif // WORKOUTDATA_H

