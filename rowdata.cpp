#include "rowdata.h"

rowData::rowData()
{

}

rowData::~rowData()
{

}

QString rowData::getDescription() {
    return description;
}


int rowData::getValue() {
    return value;
}


QString rowData::getUnit() {
    return unit;
}

void rowData::setDescription(QString description) {
    this->description = description;
}

void rowData::setValue(int value) {
    this->value = value;
}


void rowData::setUnit(QString unit) {
    this->unit = unit;
}


