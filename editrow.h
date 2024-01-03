#ifndef EDITROW_H
#define EDITROW_H

#include <QWidget>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>
#include <QDebug>
#include <QMap>
#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QGroupBox>
#include <QPushButton>
#include <QDateTime>
#include <QDateTimeEdit>

class EditRow : public QWidget
{
    Q_OBJECT
public:
    explicit EditRow(QWidget *parent = nullptr, QString description = "", int reps = 0, QString units = "", QDateTime date = QDateTime::currentDateTime());
    ~EditRow();

    QLineEdit* getDescription();
    QLineEdit* getReps();
    QLineEdit* getUnits();
    QDateTimeEdit* getDate();

    void setDescription(QString description);
    void setReps(int reps);
    void setUnits(QString reps);
    void setDate(QDateTime date);

private:
    QGroupBox mainBox;

    QLineEdit* description;
    QLineEdit* reps;
    QLineEdit* units;
    QDateTimeEdit* editDate;

    int rowHeight = 30;
    int repsUnitLabelWidth = 100;
    int dateWidth = 150;
};

#endif // EDITROW_H
