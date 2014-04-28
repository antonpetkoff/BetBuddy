#include "TeamValueWidget.h"

#include <QGridLayout>
#include <QGroupBox>
#include <QVector>
#include <QLabel>
#include <QLineEdit>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QPushButton>
#include <QSpacerItem>
#include <QFrame>
#include <QDialogButtonBox>

TeamValueWidget::TeamValueWidget(QWidget *parent) :
    QWidget(parent)
{
    avarageTeamRating = 7.0;

    mainLayout = new QGridLayout(this);
    rateLayout = new QGridLayout();
    resultLayout = new QGridLayout();

// fill rate layout
    for(int i=0;i<4;i++)
    {
        labels.insert(i, new QLabel());
        labels[i]->setAlignment(Qt::AlignHCenter);
    }
    labels[0]->setText("Player Name");
    rateLayout->addWidget(labels[0],0,0,1,2);
    labels[1]->setText("Overall Skill");
    rateLayout->addWidget(labels[1],0,2,1,1);
    labels[2]->setText("Current Form");
    rateLayout->addWidget(labels[2],0,3,1,2);
    labels[3]->setText("Player Rating");
    rateLayout->addWidget(labels[3],0,5,1,1);

    for(int i=0;i<11;i++)
    {
        playerNumber.insert(i,new QLabel(QString::number(i+1) + ":"));
        rateLayout->addWidget(playerNumber[i],i+1,0,1,1);

        playerName.insert(i, new QLineEdit());
        rateLayout->addWidget(playerName[i],i+1,1,1,1);

        playerSkill.insert(i, new QDoubleSpinBox());
        playerSkill[i]->setDecimals(1);
        playerSkill[i]->setMinimum(1.0);
        playerSkill[i]->setMaximum(10.0);
        playerSkill[i]->setSingleStep(0.1);
        playerSkill[i]->setValue(7.0);
        playerSkill[i]->setAlignment(Qt::AlignHCenter);
        rateLayout->addWidget(playerSkill[i],i+1,2,1,1);

        playerFormSlider.insert(i, new QSlider(Qt::Horizontal));
        playerFormSlider[i]->setMinimum(80);
        playerFormSlider[i]->setMaximum(120);
        playerFormSlider[i]->setValue(100);
        rateLayout->addWidget(playerFormSlider[i],i+1,3,1,1);

        playerFormLabel.insert(i, new QLabel("100"));
        rateLayout->addWidget(playerFormLabel[i],i+1,4,1,1);

        playerRating.insert(i, new QLabel("7.00"));
        playerRating[i]->setAlignment(Qt::AlignHCenter);
        rateLayout->addWidget(playerRating[i],i+1,5,1,1);

        connect(playerFormSlider[i], SIGNAL(valueChanged(int)), playerFormLabel[i], SLOT(setNum(int)));
        connect(playerFormSlider[i], SIGNAL(valueChanged(int)), this, SLOT(calculate()));
        connect(playerSkill[i], SIGNAL(valueChanged(double)), this, SLOT(calculate()));
    }

// fill result layout
    //pushCalculate = new QPushButton("Calculate");
    //resultLayout->addWidget(pushCalculate,0,0,1,1);
    pushReset = new QPushButton("Reset Values");
    resultLayout->addWidget(pushReset,1,0,1,1);
    pushClear = new QPushButton("Clear Names");
    resultLayout->addWidget(pushClear,2,0,1,1);
    resultGroupBox = new QGroupBox("Results:");
    resultLayout->addWidget(resultGroupBox,0,1,3,1);

    // fill group box Results:
    resultGroupLayout = new QGridLayout(resultGroupBox);

    labels.insert(4, new QLabel("Avarage Team Skill"));
    resultGroupLayout->addWidget(labels[4],0,0,1,1);

    teamSkills = new QLabel("7.0");
    teamSkills->setAlignment(Qt::AlignRight);
    resultGroupLayout->addWidget(teamSkills,0,1,1,1);

    labels.insert(5, new QLabel("Avarage Team Form"));
    resultGroupLayout->addWidget(labels[5],1,0,1,1);

    teamForm = new QLabel("100.00 %");
    teamForm->setAlignment(Qt::AlignRight);
    resultGroupLayout->addWidget(teamForm,1,1,1,1);

    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::HLine);
    resultGroupLayout->addWidget(line,2,0,1,2);

    labels.insert(6, new QLabel("Avarage Team Rating"));
    resultGroupLayout->addWidget(labels[6],3,0,1,1);

    teamRating = new QLabel("7.00");
    teamRating->setAlignment(Qt::AlignRight);
    resultGroupLayout->addWidget(teamRating,3,1,1,1);

// fill main layout
    mainLayout->addLayout(rateLayout,0,0,1,1);

    mainLayout->addLayout(resultLayout,1,0,1,1);

    QSpacerItem *verticalSpacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Expanding);
    mainLayout->addItem(verticalSpacer,2,0,1,1);

// make final connections
    //connect(pushCalculate, SIGNAL(clicked()), this, SLOT(calculate()));
    connect(pushReset, SIGNAL(clicked()), this, SLOT(resetValues()));
    connect(pushClear, SIGNAL(clicked()), this, SLOT(clearNames()));
}


void TeamValueWidget::calculate()
{
    avarageTeamSkill = 0;
    avarageTeamForm = 0;
    avarageTeamRating = 0;

    for(int i=0;i<11;i++)
    {
        avarageTeamSkill += playerSkill[i]->value();
        avarageTeamForm += playerFormSlider[i]->value();
        playerRating[i]->setText(QString::number(playerSkill[i]->value() * playerFormSlider[i]->value()/100.0,'f',2));
    }
    avarageTeamSkill /= 11;
    avarageTeamForm /= 11;
    avarageTeamRating = avarageTeamSkill * avarageTeamForm/100.0;

    teamSkills->setText(QString::number(avarageTeamSkill,'f',1));
    teamForm->setText(QString::number(avarageTeamForm,'f',2) + " %");
    teamRating->setText(QString::number(avarageTeamRating,'f',2));
}

void TeamValueWidget::resetValues()
{
    for(int i=0;i<11;i++)
    {
        playerSkill[i]->setValue(7.0);
        playerFormSlider[i]->setValue(100);
    }
}

void TeamValueWidget::clearNames()
{
    for(int i=0;i<11;i++)
    {
        playerName[i]->setText("");
    }
}
