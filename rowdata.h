#ifndef ROWDATA_H
#define ROWDATA_H

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

class RowData
{
public:
    RowData();
    RowData(int uniqueID, QString description, int value, QString unit);
    ~RowData();

    int getUniqueID();
    QString getDescription();
    int getValue();
    QString getUnit();

    void setUniqueID(int uniqueID);
    void setDescription(QString description);
    void setValue(int value);
    void setUnit(QString unit);

    QString toString();

private:
    int uniqueID; // it is the index of the list
    QString description;
    int value;
    QString unit;
};

inline QDataStream& operator<<( QDataStream &out, RowData& t) {
    out << t.getUniqueID();
    out << t.getDescription();
    out << t.getValue();
    out << t.getUnit();

    return out;
}


inline QDataStream& operator>>( QDataStream &in, RowData& t) {
    int tempUniqueID;
    QString tempDescription;
    int tempValue;
    QString tempUnit;

    in >> tempUniqueID;
    in >> tempDescription;
    in >> tempValue;
    in >> tempUnit;

    t.setUniqueID(tempUniqueID);
    t.setDescription(tempDescription);
    t.setValue(tempValue);
    t.setUnit(tempUnit);

    return in;
}

#endif // ROWDATA_H
