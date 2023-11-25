#include "rowdata.h"

RowData::RowData()
{

}

RowData::RowData(QString description, int value, QString unit) {
    this->setDescription(description);
    this->setValue(value);
    this->setUnit(unit);
}

RowData::~RowData()
{

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
    QString dataStr = "[" + getDescription() + ", " + QString::number(getValue()) + ", " + getUnit() + "]";
    return dataStr;
}
