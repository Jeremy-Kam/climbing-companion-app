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

class EditRow : public QWidget
{
    Q_OBJECT
public:
    explicit EditRow(QWidget *parent = nullptr);

    QLineEdit* getDescription();
    QLineEdit* getReps();
    QLineEdit* getUnits();

    void setDescription(QString description);
    void setReps(int reps);
    void setUnits(QString reps);

private:
    QGroupBox mainBox;

    QLineEdit* description;
    QLineEdit* reps;
    QLineEdit* units;

    int rowHeight = 30;
    int repsUnitLabelWidth = 100;
};

#endif // EDITROW_H
