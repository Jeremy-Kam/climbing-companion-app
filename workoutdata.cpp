#include "workoutdata.h"

WorkoutData::WorkoutData() {

}


WorkoutData::~WorkoutData() {
    workoutHistory.clear();
}


QMap<QDateTime, RowData> WorkoutData::getWorkoutHistory() {
    return workoutHistory;
}

RowData WorkoutData::getLatestRowData() {
    return workoutHistory.toStdMap().rbegin()->second;
}


void WorkoutData::setWorkoutHistory(QMap<QDateTime, RowData> newData) {
    this->workoutHistory = newData;
}

void WorkoutData::insertToWorkoutHistory(QDateTime date, RowData data) {
    this->workoutHistory.insert(date, data);
}

void WorkoutData::printAllData() {
    for(auto x: workoutHistory.toStdMap()) {
        qDebug() << x.first << ": " << x.second.toString() << " | ";
    }
}

QString WorkoutData::toString() {
    QString dataStr = "";
    for(auto x: workoutHistory.toStdMap()) {
        dataStr += x.first.toString() + ": " + x.second.toString() + '\n';
    }

    return dataStr;
}

void WorkoutData::openEditWindow() {
    qDebug() << "window open";
}
