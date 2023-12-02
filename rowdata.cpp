#include "rowdata.h"

RowData::RowData()
{

}

RowData::RowData(int uniqueID, QString description, int value, QString unit) {
    this->setUniqueID(uniqueID);
    this->setDescription(description);
    this->setValue(value);
    this->setUnit(unit);
}

RowData::~RowData()
{

}

int RowData::getUniqueID() {
    return uniqueID;
}

QString RowData::getDescription() {
    return description;
}


int RowData::getValue() {
    return value;
}


QString RowData::getUnit() {
    return unit;
}

void RowData::setUniqueID(int uniqueID) {
    this->uniqueID = uniqueID;
}

void RowData::setDescription(QString description) {
    this->description = description;
}

void RowData::setValue(int value) {
    this->value = value;
}


void RowData::setUnit(QString unit) {
    this->unit = unit;
}

QString RowData::toString() {
    QString dataStr = "[" + QString::number(getUniqueID()) + ", " + getDescription() + ", " + QString::number(getValue()) + ", " + getUnit() + "]";
    return dataStr;
}
