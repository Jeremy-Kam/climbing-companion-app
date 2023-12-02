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
        /*
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


        QDataStream in(&file);    // read the data serialized from the file

        in >> workoutList;

        qDebug() << "Number of elements: " << QString::number(workoutList.size());

        for(int i = 0; i < workoutList.size(); ++i) {
            WorkoutRow* newRow = new WorkoutRow(mainBox);
            boxVLayout->addWidget(newRow);
            listOfWorkoutRows.push_back(newRow);

            RowData latestRowData = workoutList[i].getLatestRowData();

            newRow->setDescription(latestRowData.getDescription());
            newRow->setReps(latestRowData.getValue());
            newRow->setUnits(latestRowData.getUnit());
        }

        // printData();

        /*
        while(in.atEnd() == false) {
            qDebug() << "Runs";
            WorkoutData temp;
            in >> temp;

            qDebug() << temp.toString();

            workoutList.push_back(temp);


            // WorkoutRow* newRow = new WorkoutRow(mainBox);
            // boxVLayout->addWidget(newRow);
            // listOfWorkoutRows.push_back(newRow);

            // RowData latestRowData = temp.getLatestRowData();


            // So the text does not show properly, but the function can get called without segmentation fault. However, printing the value causes segmentation fault?
            // QString test = latestRowData.getDescription();

            // newRow->setDescription(latestRowData.getDescription());
            // newRow->setReps(latestRowData.getValue());
            // newRow->setUnits(latestRowData.getUnit());

            // qDebug() << latestRowData.getDescription() << " " << QString::number(latestRowData.getValue()) << " " << latestRowData.getUnit();



            qDebug() << "Ends";
        }

        */

        qDebug() << "Exits";
    }
}

ClimbingApp::~ClimbingApp()
{
    QFile file("climbingworkoutdata.dat");
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);   // we will serialize the data into the file

    for(int i = 0; i < workoutList.size(); ++i) {
        out << workoutList[i];
        qDebug() << "Loaded into .bat file";
        // qDebug() << x.toString();
    }

    qDebug() << "Destructor is run";

    // printData();

    delete ui;
}


void ClimbingApp::setWorkoutList(std::vector<WorkoutData> workoutList) {
    this->workoutList = workoutList;
}

QString ClimbingApp::toString() {
    QString workoutStr = "";
    for(WorkoutData x: workoutList) {
        workoutStr += x.toString() + " | ";
        qDebug() << "Went though once";
    }

    return workoutStr;
}

void ClimbingApp::printData() {
    qDebug() << workoutList[0].getWorkoutHistory().toStdMap().begin()->first << ": " << toString();
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

    std::vector<WorkoutData> tempWorkoutList;

    for(int i = 0; i < workoutList.size(); ++i) {
        RowData tempRowData;

        tempRowData.setUniqueID(i);
        tempRowData.setDescription(listOfWorkoutRows[i]->getDescription()->text());

        if(isInt(listOfWorkoutRows[i]->getReps()->text())) {
            tempRowData.setValue(listOfWorkoutRows[i]->getReps()->text().toInt());
        } else {
            qDebug() << "Not integer value. Replaced with 0";
            tempRowData.setValue(0);
        }

        tempRowData.setUnit(listOfWorkoutRows[i]->getUnits()->text());

        // Maybe use overloaded QTimeZone to set it to the local time

        WorkoutData tempWorkoutData;
        tempWorkoutData.insertToWorkoutHistory(QDateTime::currentDateTime(), tempRowData);
        tempWorkoutList.push_back(tempWorkoutData);
    }

    setWorkoutList(tempWorkoutList);

    // printData();

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

    WorkoutRow* newRow = new WorkoutRow(mainBox);

    boxVLayout->addWidget(newRow);

    listOfWorkoutRows.push_back(newRow);

    WorkoutData temp;
    workoutList.push_back(temp);
}


void ClimbingApp::on_actionDelete_Row_triggered()
{
    if(listOfWorkoutRows.empty()) {
        qDebug() << "List is empty";
        return;
    }

    WorkoutRow* temp = listOfWorkoutRows[listOfWorkoutRows.size() - 1];
    listOfWorkoutRows.pop_back();
    delete temp;
    temp = nullptr;
    qDebug() << "Delete row";
}


bool ClimbingApp::isInt(QString str) {
    for(int i = 0; i < str.size(); ++i) {
        if(!str[i].isDigit()) {
            return false;
        }
    }
    return true;
}

// cd Onedrive/Documents/Qt/Projects/ClimbingApp

