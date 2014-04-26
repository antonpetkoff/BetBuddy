#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include "StatsWidget.h"
#include <QDialog>
#include <QString>
#include <QGridLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QSpacerItem>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>

class StatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatsDialog(const QString & host = "Host Team",
                         const QString & guest = "Guest Team",
                         QWidget *parent = 0);
    ~StatsDialog();

    double getHostValue() {return home->calculateValue();}
    double getGuestValue() {return away->calculateValue();}
private slots:
    void numberOfMatchesChanged(int value);
    void editClicked();
    void calculateClicked();
private:
    QString hostName;
    QString guestName;

    QSpinBox *spinNumMatches;
    QPushButton *editButton;
    QPushButton *calculateButton;
    QLabel *homeValue;
    QLabel *awayValue;

    StatsWidget *home;
    StatsWidget *away;

    QDialogButtonBox *buttonBox;
};

#endif // STATSDIALOG_H
