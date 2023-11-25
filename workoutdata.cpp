#include "workoutdata.h"

WorkoutData::WorkoutData() {

}


WorkoutData::~WorkoutData() {
    workoutHistory.clear();
}


QMap<QDateTime, RowData> WorkoutData::getWorkoutHistory() {
    return workoutHistory;
}


void WorkoutData::setWorkoutHistory(QMap<QDateTime, RowData> newData) {
    this->workoutHistory = newData;
}

void WorkoutData::insertToWorkoutHistory(QDateTime date, RowData data) {
    this->workoutHistory.insert(date, data);
}

QString WorkoutData::toString() {
    QString dataStr = "";
    for(auto x: workoutHistory.toStdMap()) {
        dataStr += x.first.toString() + ": " + x.second.toString() + '\n';
    }

    return dataStr;
}
