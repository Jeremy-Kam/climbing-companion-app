#include "editwindow.h"

EditWindow::EditWindow(QWidget *parent, WorkoutData data, int index)
    : QWidget{parent}
{
    this->index = index;

    this->resize(1000, 500);

    QVBoxLayout* editWindowMainVLayout = new QVBoxLayout(this);

    this->editWindowVLayout = new QVBoxLayout();

    QWidget* editWindowscrollAreaContent = new QWidget();
    editWindowscrollAreaContent->setLayout(editWindowVLayout);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(editWindowscrollAreaContent);

    editWindowMainVLayout->addWidget(scrollArea);

    QWidget* editWindowColumnNameWidget = new QWidget(scrollArea);
    editWindowVLayout->addWidget(editWindowColumnNameWidget);

    QHBoxLayout *editWindowColumnNameLayout = new QHBoxLayout(editWindowColumnNameWidget);

    QLabel* editWindowDescription = new QLabel("Description", editWindowColumnNameWidget);
    editWindowDescription->setFixedHeight(labelHeight);
    editWindowColumnNameLayout->addWidget(editWindowDescription);

    QLabel* editWindowReps = new QLabel("Reps/Weight", editWindowColumnNameWidget);
    editWindowReps->setFixedHeight(labelHeight);
    editWindowReps->setFixedWidth(repsUnitsWidth);
    editWindowColumnNameLayout->addWidget(editWindowReps);

    QLabel* editWindowUnits = new QLabel("Units", editWindowColumnNameWidget);
    editWindowUnits->setFixedHeight(labelHeight);
    editWindowUnits->setFixedWidth(repsUnitsWidth);
    editWindowColumnNameLayout->addWidget(editWindowUnits);

    QLabel* editWindowDateEdit = new QLabel("Date changed", editWindowColumnNameWidget);
    editWindowDateEdit->setFixedHeight(labelHeight);
    editWindowDateEdit->setFixedWidth(dateEditWidth);
    editWindowColumnNameLayout->addWidget(editWindowDateEdit);


    QMap<QDateTime, RowData> workoutHistory = data.getWorkoutHistory();

    for(auto x: workoutHistory.toStdMap()) {
        EditRow* temp = new EditRow(nullptr, x.second.getDescription(), x.second.getValue(), x.second.getUnit(), x.first);
        editWindowVLayout->addWidget(temp);
        listOfEditRows.push_back(temp);
    }

    buttonLayout = new QHBoxLayout();

    QPushButton* addButton = new QPushButton("Add Row");
    QPushButton* deleteButton = new QPushButton("Delete Row");
    QPushButton* saveButton = new QPushButton("Save");

    buttonLayout->addWidget(addButton);
    buttonLayout->addWidget(deleteButton);
    buttonLayout->addWidget(saveButton);

    editWindowMainVLayout->addLayout(buttonLayout);

    QObject::connect(addButton, &QPushButton::clicked, this, &EditWindow::addButtonPressed);
    QObject::connect(deleteButton, &QPushButton::clicked, this, &EditWindow::deleteButtonPressed);
    QObject::connect(saveButton, &QPushButton::clicked, this, &EditWindow::saveButtonPressed);

    this->setAttribute(Qt::WA_DeleteOnClose);
    this->show();
}

EditWindow::~EditWindow() {
    QMap<QDateTime, RowData> temp = getNewData();
    qDebug() << "Exited window";
    for(auto x: temp.toStdMap()) {
        qDebug() << x.first << ": " << x.second.getUniqueID() << " " << x.second.getDescription() << " " << x.second.getValue() << " " << x.second.getUnit();
    }
}

QMap<QDateTime, RowData> EditWindow::getNewData() {
    QMap<QDateTime, RowData> newData;
    for(int i = 0; i < listOfEditRows.size(); ++i) {
        RowData temp;
        temp.setUniqueID(index);
        temp.setDescription(listOfEditRows[i]->getDescription()->text());

        if(isInt(listOfEditRows[i]->getReps()->text())) {
            temp.setValue(listOfEditRows[i]->getReps()->text().toInt());
        } else {
            qDebug() << "Not integer value. Replaced with 0";
            temp.setValue(0);
        }

        temp.setUnit(listOfEditRows[i]->getUnits()->text());

        newData.insert(listOfEditRows[i]->getDate()->dateTime(), temp);
    }

    return newData;
}

bool EditWindow::isInt(QString str) {
    for(int i = 0; i < str.size(); ++i) {
        if(!str[i].isDigit()) {
            return false;
        }
    }
    return true;
}

void EditWindow::addButtonPressed() {
    qDebug() << "Add Button Pressed";
    EditRow* temp = new EditRow();
    editWindowVLayout->addWidget(temp);
    listOfEditRows.push_back(temp);
}

void EditWindow::deleteButtonPressed() {
    qDebug() << "Delete Button Pressed";
    if(listOfEditRows.empty()) {
        qDebug() << "No edit rows to delete";
        return;
    }
    EditRow* temp = listOfEditRows[listOfEditRows.size() - 1];
    listOfEditRows.pop_back();
    delete temp;
    temp = nullptr;
}

void EditWindow::saveButtonPressed() {
    qDebug() << "Save Button Pressed";
    emit savedDataForRow(index);
}
