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

        QLineSeries *lseries = new QLineSeries();

        QMap<QDateTime, RowData> tempWorkoutHistory = workoutList[0].getWorkoutHistory();

        int minValue = std::numeric_limits<int>::max();
        int maxValue = -1;

        // TODO: Set manual axis so user knows when it was updated
        for(auto x: tempWorkoutHistory.toStdMap()) {
            lseries->append(x.first.toMSecsSinceEpoch(), x.second.getValue());
            minValue = std::min(minValue, x.second.getValue());
            maxValue = std::max(maxValue, x.second.getValue());
        }

        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(lseries);
        // chart->createDefaultAxes();

        // Customize the title font
        QFont font;
        font.setPixelSize(18);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle(workoutList[0].getLatestRowData().getDescription());

        // Change the line color and weight
        QPen pen(QRgb(0x000000));
        pen.setWidth(3);
        lseries->setPen(pen);

        QList tempVertical = chart->axes(Qt::Vertical);

        // tempHorizontal.back()->setRange(-35, 135);

        QDateTimeAxis* axisX = new QDateTimeAxis();
        axisX->setTickCount(10);
        axisX->setFormat("dd MMM yyyy");
        axisX->setTitleText("Date");
        chart->addAxis(axisX, Qt::AlignBottom);
        lseries->attachAxis(axisX);

        // TODO, distinguish between reps and weight, and update axis title accordingly
        QValueAxis* axisY = new QValueAxis();
        axisY->setLabelFormat("%i");
        axisY->setTitleText("Units [" + workoutList[0].getLatestRowData().getUnit() + "]");
        axisY->setRange(std::max(minValue - 2, 0), maxValue + 2);
        chart->addAxis(axisY, Qt::AlignLeft);
        lseries->attachAxis(axisY);


        chart->setAnimationOptions(QChart::AllAnimations);


        // Used to display the chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        mainVLayout->addWidget(chartView);

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
    for(WorkoutData x: workoutList) {
        x.printAllData();
        qDebug();
    }
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

        workoutList[i].insertToWorkoutHistory(QDateTime::currentDateTime(), tempRowData);
    }

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

