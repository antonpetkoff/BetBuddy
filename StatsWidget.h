#ifndef STATSWIDGET_H
#define STATSWIDGET_H

#include <QWidget>
#include <QVector>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QSpinBox>
#include <QHBoxLayout>
#include <QComboBox>
#include <QSpacerItem>
#include <QPushButton>

class StatsWidget : public QWidget
{
    Q_OBJECT
public:
    explicit StatsWidget(int matches = 5, QWidget *parent = 0);
    int getNumberOfMatches() {return numberOfMatches;}
    void editMatchRows(int value);
    double calculateValue();
private:
    static const int guestBonus = 1;

    void addMatchRow(int i);
    double factor(int teamQuality);
    int numberOfMatches;
    QGridLayout *mainLayout;

    QGridLayout *statsLayout;
    QVector<QComboBox *> venue;
    QVector<QSpinBox *> opponent;
    QVector<QSpinBox *> hostGoals;
    QVector<QSpinBox *> guestGoals;
};

#endif // STATSWIDGET_H
