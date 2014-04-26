#ifndef MAINDIALOG_H
#define MAINDIALOG_H

#include "StatsDialog.h"
#include "TeamValueDialog.h"
#include <QDialog>
#include <QString>
#include <QGridLayout>
#include <QGroupBox>
#include <QLabel>
#include <QSlider>
#include <QPushButton>
#include <QSpacerItem>
#include <QFrame>
#include <QDoubleSpinBox>
#include <QCheckBox>
#include <QMessageBox>
#include <QException>

class MainDialog : public QDialog
{
    Q_OBJECT

public:
    MainDialog(const QString & host = "Host Team",
               const QString & guest = "Guest Team",
               QWidget *parent = 0);
    ~MainDialog();
private slots:
    void changeTeamValueWeight(int value)   {teamValueWeightLabel->setText(QString::number(value) + "%");}
    void changeStatsWeight(int value)       {statsWeightLabel->setText(QString::number(value) + "%");}
    void changeHostFactorWeight(int value)  {hostFactorWeightLabel->setText(QString::number(value) + "%");}
    void distributeFactorsWeight();

    void teamValueClicked();
    void statsClicked();
    void calculateClicked();
private:
    QString hostName;
    QString guestName;
    QGridLayout *mainLayout;
    QGridLayout *evaluationLayout;
    QGroupBox *evaluationGroup;

    TeamValueDialog teamValueDialog;
    QPushButton *teamValueButton;
    QDoubleSpinBox *teamValueSpinHost;
    QDoubleSpinBox *teamValueSpinGuest;
    QSlider *teamValueSlider;
    QLabel *teamValueWeightLabel;
    QCheckBox *teamValueCheck;
    double teamValueWeight;  // stored as % in decimal form

    StatsDialog statsDialog;
    QPushButton *statsButton;
    QDoubleSpinBox *statsSpinHost;
    QDoubleSpinBox *statsSpinGuest;
    QSlider *statsSlider;
    QLabel *statsWeightLabel;
    QCheckBox *statsCheck;
    double statsWeight;  // stored as % in decimal form

    QPushButton *hostFactorButton;
    QDoubleSpinBox *hostFactorSpin;
    QSlider *hostFactorSlider;
    QLabel *hostFactorWeightLabel;
    QCheckBox *hostFactorCheck;
    double hostFactorWeight; // stored as % in decimal form

    QPushButton *calculateButton;

    QGroupBox *resultGroup;
    QGridLayout *resultLayout;
    QLabel *hostPointsLabel;
    QLabel *guestPointsLabel;
    QLabel *hostChanceLabel;
    QLabel *guestChanceLabel;
    double hostChance;
    double guestChance;
};

#endif // DIALOG_H
