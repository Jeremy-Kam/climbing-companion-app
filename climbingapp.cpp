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

        // QScrollArea *scrollArea = new QScrollArea();
        // scrollArea->setBackgroundRole(QPalette::Highlight);
        // scrollArea->setWidget(ui->centralwidget);
        // scrollArea->setWidgetResizable(true);
        // scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

        mainVLayout = new QVBoxLayout(ui->centralwidget);

        ui->centralwidget->setLayout(mainVLayout);

        mainBox = new QGroupBox("Dishes:", ui->centralwidget);
        boxVLayout = new QVBoxLayout(mainBox);

        mainVLayout->addWidget(mainBox);

        // boxVLayout->addWidget(scrollArea);


        // Column name
        QWidget* columnNameWidget = new QWidget(mainBox);
        boxVLayout->addWidget(columnNameWidget);

        QHBoxLayout *columnNameLayout = new QHBoxLayout(columnNameWidget);

        QLabel* description = new QLabel("Description", columnNameWidget);
        description->setFixedHeight(labelHeight);
        columnNameLayout->addWidget(description);

        QLabel* reps = new QLabel("Reps/Weight", columnNameWidget);
        reps->setFixedHeight(labelHeight);
        reps->setFixedWidth(repsUnitsWidth);
        columnNameLayout->addWidget(reps);

        QLabel* units = new QLabel("Units", columnNameWidget);
        units->setFixedHeight(labelHeight);
        units->setFixedWidth(repsUnitsWidth);
        columnNameLayout->addWidget(units);

        QLabel* editSpacer = new QLabel();
        editSpacer->setFixedHeight(labelHeight);
        editSpacer->setFixedWidth(labelHeight);
        columnNameLayout->addWidget(editSpacer);

        QLabel* deleteSpacer = new QLabel();
        deleteSpacer->setFixedHeight(labelHeight);
        deleteSpacer->setFixedWidth(labelHeight);
        columnNameLayout->addWidget(deleteSpacer);


        QDataStream in(&file);    // read the data serialized from the file

        in >> workoutList;

        qDebug() << "Number of elements: " << QString::number(workoutList.size());

        for(int i = 0; i < workoutList.size(); ++i) {
            WorkoutRow* newRow = new WorkoutRow(mainBox, listOfWorkoutRows.size());

            QObject::connect(newRow, &WorkoutRow::openEditWindow, this, &ClimbingApp::openEditWindow);
            QObject::connect(newRow, &WorkoutRow::deleteRow, this, &ClimbingApp::deleteRowAtIndex);

            boxVLayout->addWidget(newRow);
            listOfWorkoutRows.push_back(newRow);

            RowData latestRowData = workoutList[i].getLatestRowData();

            newRow->setDescription(latestRowData.getDescription());
            newRow->setReps(latestRowData.getValue());
            newRow->setUnits(latestRowData.getUnit());
        }

        // printData();

        graphVLayout = new QVBoxLayout();


        QWidget* scrollAreaContent = new QWidget();
        scrollAreaContent->setLayout(graphVLayout);
        QScrollArea* scrollArea = new QScrollArea();
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        scrollArea->setWidget(scrollAreaContent);

        mainVLayout->addWidget(scrollArea);

        createCharts();

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

    updateCharts();

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
    WorkoutRow* newRow = new WorkoutRow(mainBox, listOfWorkoutRows.size());

    QObject::connect(newRow, &WorkoutRow::openEditWindow, this, &ClimbingApp::openEditWindow);
    QObject::connect(newRow, &WorkoutRow::deleteRow, this, &ClimbingApp::deleteRowAtIndex);

    boxVLayout->addWidget(newRow);

    listOfWorkoutRows.push_back(newRow);

    WorkoutData temp;
    workoutList.push_back(temp);
}


void ClimbingApp::on_actionDelete_Row_triggered()
{
    deleteRowAtIndex(listOfWorkoutRows.size() - 1);
}


bool ClimbingApp::isInt(QString str) {
    for(int i = 0; i < str.size(); ++i) {
        if(!str[i].isDigit()) {
            return false;
        }
    }
    return true;
}

void ClimbingApp::openEditWindow(int index) {
    qDebug() << "Opening edit window for: " + QString::number(index);

    QWidget* window = new QWidget();
    window->resize(500, 500);

    QVBoxLayout* editWindowMainVLayout = new QVBoxLayout(window);

    QVBoxLayout* editWindowVLayout = new QVBoxLayout();

    QWidget* editWindowscrollAreaContent = new QWidget();
    editWindowscrollAreaContent->setLayout(editWindowVLayout);
    QScrollArea* scrollArea = new QScrollArea();
    scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(editWindowscrollAreaContent);

    editWindowMainVLayout->addWidget(scrollArea);

    editWindowVLayout->addWidget(new EditRow());

    window->show();
}

void ClimbingApp::deleteRowAtIndex(int index) {
    if(listOfWorkoutRows.empty()) {
        qDebug() << "List is empty";
        return;
    }

    WorkoutRow* temp = listOfWorkoutRows[index];
    listOfWorkoutRows.erase(listOfWorkoutRows.begin() + index);
    delete temp;
    temp = nullptr;

    QChartView* tempCV = listOfChartViews[index];
    listOfChartViews.erase(listOfChartViews.begin() + index);
    delete tempCV;
    tempCV = nullptr;

    for(int i = index; i < listOfWorkoutRows.size(); ++i) {
        listOfWorkoutRows[i]->setIndex(i);
    }

    workoutList.erase(workoutList.begin() + index);

    updateCharts();

    qDebug() << "Delete row";
}

void ClimbingApp::createCharts() {
    for(int i = 0; i < workoutList.size(); ++i) {
        // We currently have no way of referencing the series
        QLineSeries *lseries = new QLineSeries();

        QMap<QDateTime, RowData> tempWorkoutHistory = workoutList[i].getWorkoutHistory();

        int minValue = std::numeric_limits<int>::max();
        int maxValue = -1;

        // Data point set to today's date on the graph so it doesn't cut off at the last time it was changed
        int latestValue;

        // TODO: Set manual axis so user knows when it was updated
        for(auto x: tempWorkoutHistory.toStdMap()) {
            latestValue = x.second.getValue();
            lseries->append(x.first.toMSecsSinceEpoch(), latestValue);
            minValue = std::min(minValue, latestValue);
            maxValue = std::max(maxValue, latestValue);
        }

        lseries->append(QDateTime::currentMSecsSinceEpoch(), latestValue);

        QChart *chart = new QChart();
        chart->legend()->hide();
        chart->addSeries(lseries);
        // chart->createDefaultAxes();

        // Customize the title font
        QFont font;
        font.setPixelSize(18);
        chart->setTitleFont(font);
        chart->setTitleBrush(QBrush(Qt::black));
        chart->setTitle(workoutList[i].getLatestRowData().getDescription());

        // Change the line color and weight
        QPen pen((QRgb(graphColors[rand() % graphColors.size()])));
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
        axisY->setTitleText("Reps/Weight [" + workoutList[i].getLatestRowData().getUnit() + "]");
        axisY->setRange(std::max(minValue - 2, 0), maxValue + 2);
        chart->addAxis(axisY, Qt::AlignLeft);
        lseries->attachAxis(axisY);


        chart->setAnimationOptions(QChart::AllAnimations);

        // Used to display the chart
        QChartView *chartView = new QChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

        chartView->setFixedHeight(500);

        graphVLayout->addWidget(chartView);

        listOfChartViews.push_back(chartView);
    }
}

void ClimbingApp::updateCharts() {
    while(!listOfChartViews.empty()) {
        QChartView* tempCV = listOfChartViews[0];
        listOfChartViews.erase(listOfChartViews.begin());
        delete tempCV;
        tempCV = nullptr;
    }

    createCharts();

}

// cd Onedrive/Documents/Qt/Projects/ClimbingApp

