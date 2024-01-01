#include "editwindow.h"

EditWindow::EditWindow(QWidget *parent, WorkoutData data, int index)
    : QWidget{parent}
{
    this->index = index;

    this->resize(1000, 500);

    QVBoxLayout* editWindowMainVLayout = new QVBoxLayout(this);

    QVBoxLayout* editWindowVLayout = new QVBoxLayout();

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


    editWindowVLayout->addWidget(new EditRow());

    this->show();
}

EditWindow::~EditWindow() {

}
