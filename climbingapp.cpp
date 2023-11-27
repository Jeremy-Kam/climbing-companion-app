#include "climbingapp.h"
#include "ui_climbingapp.h"

ClimbingApp::ClimbingApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ClimbingApp)
{

    ui->setupUi(this);

    QFile file("climbingworkoutdata.dat");
    if(!file.open(QIODevice::ReadOnly)) {
        // this might happen if app is opened for the first time
        qDebug() << "File not open" << file.error();
    }else{
        qDebug() << "File is open";
        QDataStream in(&file);    // read the data serialized from the file
        in >> workoutList;

        std::map<QDateTime, RowData> tempMap = workoutList.getWorkoutHistory().toStdMap();

        QString tempD;
        int tempR;
        QString tempU;
        for(auto x: tempMap) {
            tempD = x.second.getDescription();
            tempR = x.second.getValue();
            tempU = x.second.getUnit();
        }


        // ui->description->document()->setPlainText(tempD);
        // ui->reps->document()->setPlainText(QString::number(tempR));
        // ui->units->document()->setPlainText(tempU);

        /*
        QVBoxLayout *layout = new QVBoxLayout(ui->centralwidget);

        ui->centralwidget->setLayout(layout);

        QGroupBox *box = new QGroupBox("Dishes:", ui->centralwidget);
        QVBoxLayout *boxLayout = new QVBoxLayout(box);

        layout->addWidget(box);

        // Column name
        QWidget* columnNameWidget = new QWidget(box);
        boxLayout->addWidget(columnNameWidget);

        QHBoxLayout *columnNameLayout = new QHBoxLayout(columnNameWidget);
        columnNameLayout->addWidget(new QLabel("Description", columnNameWidget));
        columnNameLayout->addWidget(new QLabel("Reps", columnNameWidget));
        columnNameLayout->addWidget(new QLabel("Units", columnNameWidget));
        */

        mainVLayout = new QVBoxLayout(ui->centralwidget);

        ui->centralwidget->setLayout(mainVLayout);

        mainBox = new QGroupBox("Dishes:", ui->centralwidget);
        boxVLayout = new QVBoxLayout(mainBox);

        mainVLayout->addWidget(mainBox);

        // Column name
        QWidget* columnNameWidget = new QWidget(mainBox);
        boxVLayout->addWidget(columnNameWidget);

        QHBoxLayout *columnNameLayout = new QHBoxLayout(columnNameWidget);
        columnNameLayout->addWidget(new QLabel("Description", columnNameWidget));
        columnNameLayout->addWidget(new QLabel("Reps", columnNameWidget));
        columnNameLayout->addWidget(new QLabel("Units", columnNameWidget));


    }
}

ClimbingApp::~ClimbingApp()
{
    QFile file("climbingworkoutdata.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << workoutList;

    qDebug() << "Destructor is run";

    printData();

    delete ui;
}


void ClimbingApp::setWorkoutList(WorkoutData workoutList) {
    this->workoutList = workoutList;
}

QString ClimbingApp::toString() {
    return workoutList.toString();
}

void ClimbingApp::printData() {
    qDebug() << workoutList.getWorkoutHistory().toStdMap().begin()->first << ": " << toString();
}


void ClimbingApp::on_actionSave_triggered()
{
    qDebug() << "Saved";

    // RowData* tempRowData = new RowData(ui->description->toPlainText(), ui->reps->toPlainText().toInt(), ui->units->toPlainText());


    // RowData tempRowData;
    // tempRowData.setDescription(ui->description->toPlainText());

    // TODO: Run a check if the value is actually an int
    // tempRowData.setValue(ui->reps->toPlainText().toInt());
    // tempRowData.setUnit(ui->units->toPlainText());

    // WorkoutData tempWorkoutData;
    // Maybe use overloaded QTimeZone to set it to the local time
    // tempWorkoutData.insertToWorkoutHistory(QDateTime::currentDateTime(), tempRowData);

    // setWorkoutList(tempWorkoutData);

    printData();

}


void ClimbingApp::on_actionExit_triggered()
{
    QApplication::quit();
}

void ClimbingApp::on_actionDebug_triggered()
{
    printData();
}


void ClimbingApp::on_actionAdd_Row_triggered()
{
    /*
    // Row of workout
    QWidget* workoutElementWidget = new QWidget(mainBox);
    boxVLayout->addWidget(workoutElementWidget);

    QHBoxLayout *workoutElementLayout = new QHBoxLayout(workoutElementWidget);
    workoutElementLayout->addWidget(new QLineEdit(workoutElementWidget));
    workoutElementLayout->addWidget(new QLineEdit(workoutElementWidget));
    workoutElementLayout->addWidget(new QLineEdit(workoutElementWidget));
    */

    WorkoutRow* newRow = new WorkoutRow(mainBox, boxVLayout);

    listOfWorkoutRows.push_back(newRow);

}


void ClimbingApp::on_actionDelete_Row_triggered()
{
    if(listOfWorkoutRows.empty()) {
        qDebug() << "List is empty";
        return;
    }

    WorkoutRow* temp = listOfWorkoutRows[listOfWorkoutRows.size() - 1];
    listOfWorkoutRows.pop_back();

    qDebug() << temp;

    if(temp->layout() == nullptr) {
        qDebug() << "wtf";
    }

    temp->layout()->removeWidget(temp);
    delete temp;
    temp = nullptr;
    qDebug() << "Delete row";
}

