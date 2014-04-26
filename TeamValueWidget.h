#ifndef TEAMVALUEWIDGET_H
#define TEAMVALUEWIDGET_H

#include <QWidget>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QGroupBox>
#include <QPushButton>
#include <QSpacerItem>
#include <QFrame>
#include <QGridLayout>
#include <QDialogButtonBox>

class TeamValueWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TeamValueWidget(QWidget *parent = 0);
    ~TeamValueWidget() {}

    float avarageTeamSkill;
    float avarageTeamForm;
    float avarageTeamRating;

private slots:
    void calculate();
    void resetValues();
    void clearNames();

private:
    QGridLayout *mainLayout;
    QGridLayout *rateLayout;
    QGridLayout *resultLayout;
    QGridLayout *resultGroupLayout;
    QGroupBox *resultGroupBox;

    QVector<QLabel *> labels;
    QVector<QLabel *> playerNumber;
    QVector<QLineEdit *> playerName;
    QVector<QDoubleSpinBox *> playerSkill;
    QVector<QSlider *> playerFormSlider;
    QVector<QLabel *> playerFormLabel;
    QVector<QLabel *> playerRating;

    QLabel *teamSkills;
    QLabel *teamForm;
    QLabel *teamRating;

    //QPushButton *pushCalculate;
    QPushButton *pushReset;
    QPushButton *pushClear;
};

#endif // TEAMVALUEWIDGET_H
