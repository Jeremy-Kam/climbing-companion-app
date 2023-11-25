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

        QString temp;
        for(auto x: tempMap) {
            temp = x.second.getDescription();
        }

        ui->description->document()->setPlainText(temp);
    }
}

ClimbingApp::~ClimbingApp()
{
    QFile file("climbingworkoutdata.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file
    out << workoutList;

    qDebug() << "Destructor is run";

    delete ui;
}


void ClimbingApp::setWorkoutList(WorkoutData workoutList) {
    this->workoutList = workoutList;
}

QString ClimbingApp::toString() {
    return workoutList.toString();
}

void ClimbingApp::printData() {
    qDebug() << toString();
}


void ClimbingApp::on_actionSave_triggered()
{
    qDebug() << "Saved";



    // RowData* tempRowData = new RowData(ui->description->toPlainText(), ui->reps->toPlainText().toInt(), ui->units->toPlainText());


    RowData tempRowData;
    tempRowData.setDescription(ui->description->toPlainText());

    // TODO: Run a check if the value is actually an int
    tempRowData.setValue(ui->reps->toPlainText().toInt());
    tempRowData.setUnit(ui->units->toPlainText());

    WorkoutData tempWorkoutData;
    // Maybe use overloaded QTimeZone to set it to the local time
    tempWorkoutData.insertToWorkoutHistory(QDateTime::currentDateTime(), tempRowData);

    setWorkoutList(tempWorkoutData);

    printData();

}


void ClimbingApp::on_actionExit_triggered()
{
    QApplication::quit();
}
