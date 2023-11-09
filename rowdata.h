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

class rowData
{
public:
    rowData();
    ~rowData();

    QString getDescription();
    int getValue();
    QString getUnit();

    void setDescription(QString description);
    void setValue(int value);
    void setUnit(QString unit);

private:
    QString description;
    int value;
    QString unit;
};

inline QDataStream& operator<<( QDataStream &out, rowData& t) {
    out << t.getDescription();
    out << t.getValue();
    out << t.getUnit();

    return out;
}


inline QDataStream& operator>>( QDataStream &in, rowData& t) {
    QString tempDescription;
    int tempValue;
    QString tempUnit;

    in >> tempDescription;
    in >> tempValue;
    in >> tempUnit;

    t.setDescription(tempDescription);
    t.setValue(tempValue);
    t.setUnit(tempUnit);

    return in;
}

#endif // ROWDATA_H
