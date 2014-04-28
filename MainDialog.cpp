#include "MainDialog.h"

#include "StatsDialog.h"
#include "TeamValueDialog.h"
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

MainDialog::MainDialog(const QString &host, const QString &guest, QWidget *parent)
    : QDialog(parent), hostName("<b>"+host+"</b>"), guestName("<b>"+guest+"</b>")
{
// initialization
    teamValueDialog = new TeamValueDialog();
    statsDialog = new StatsDialog();
    teamValueWeight = 0.33;
    statsWeight = 0.33;
    hostFactorWeight = 0.33;
    this->resize(400,250);
    mainLayout = new QGridLayout(this);
    evaluationGroup = new QGroupBox("Evaluate Teams:");
    evaluationLayout = new QGridLayout(evaluationGroup);

// Evaluation Layout
    QFrame *line = new QFrame();
    line->setFrameShape(QFrame::VLine);
    line->setLineWidth(4);
    evaluationLayout->addWidget(line,0,2,4,1);

// first row
    evaluationLayout->addWidget(new QLabel("<center>Factor</center>"),0,0,1,1);
    evaluationLayout->addWidget(new QLabel(hostName),0,1,1,1);
    evaluationLayout->addWidget(new QLabel(guestName),0,3,1,1);
    evaluationLayout->addWidget(new QLabel("<center>Factor Weight</center>"),0,4,1,2);
    evaluationLayout->addWidget(new QLabel("Lock"),0,6,1,1);

// second row
    evaluationLayout->addWidget(teamValueButton = new QPushButton("Team Value"),1,0,1,1);
        teamValueButton->setToolTip("Avarage team ratings");
    evaluationLayout->addWidget(teamValueSpinHost = new QDoubleSpinBox(),1,1,1,1);
        teamValueSpinHost->setRange(0,10);
        teamValueSpinHost->setDecimals(1);
        teamValueSpinHost->setSingleStep(0.1);
        teamValueSpinHost->setAlignment(Qt::AlignCenter);
    evaluationLayout->addWidget(teamValueSpinGuest = new QDoubleSpinBox(),1,3,1,1);
        teamValueSpinGuest->setRange(0,10);
        teamValueSpinGuest->setDecimals(1);
        teamValueSpinGuest->setSingleStep(0.1);
        teamValueSpinGuest->setAlignment(Qt::AlignCenter);
    evaluationLayout->addWidget(teamValueSlider = new QSlider(Qt::Horizontal),1,4,1,1);
        teamValueSlider->setRange(0,100);
        teamValueSlider->setValue(33);
    evaluationLayout->addWidget(teamValueWeightLabel = new QLabel("33%"),1,5,1,1);
    evaluationLayout->addWidget(teamValueCheck = new QCheckBox(),1,6,1,1);

    connect(teamValueSlider, SIGNAL(valueChanged(int)), this, SLOT(changeTeamValueWeight(int)));
    connect(teamValueSlider, SIGNAL(valueChanged(int)), this, SLOT(distributeFactorsWeight()));
    connect(teamValueCheck, SIGNAL(toggled(bool)), teamValueSlider, SLOT(setDisabled(bool)));
    connect(teamValueButton, SIGNAL(clicked()), this, SLOT(teamValueClicked()));

// third row
    evaluationLayout->addWidget(statsButton = new QPushButton("Statistics"),2,0,1,1);
    evaluationLayout->addWidget(statsSpinHost = new QDoubleSpinBox(),2,1,1,1);
        statsSpinHost->setRange(0,10);
        statsSpinHost->setDecimals(1);
        statsSpinHost->setSingleStep(0.1);
        statsSpinHost->setAlignment(Qt::AlignCenter);
    evaluationLayout->addWidget(statsSpinGuest = new QDoubleSpinBox(),2,3,1,1);
        statsSpinGuest->setRange(0,10);
        statsSpinGuest->setDecimals(1);
        statsSpinGuest->setSingleStep(0.1);
        statsSpinGuest->setAlignment(Qt::AlignCenter);
    evaluationLayout->addWidget(statsSlider = new QSlider(Qt::Horizontal),2,4,1,1);
        statsSlider->setRange(0,100);
        statsSlider->setValue(33);
    evaluationLayout->addWidget(statsWeightLabel = new QLabel("33%"),2,5,1,1);
    evaluationLayout->addWidget(statsCheck = new QCheckBox(),2,6,1,1);

    connect(statsSlider, SIGNAL(valueChanged(int)), this, SLOT(changeStatsWeight(int)));
    connect(statsSlider, SIGNAL(valueChanged(int)), this, SLOT(distributeFactorsWeight()));
    connect(statsCheck, SIGNAL(toggled(bool)), statsSlider, SLOT(setDisabled(bool)));
    connect(statsButton, SIGNAL(clicked()), this, SLOT(statsClicked()));

// fourth row
    evaluationLayout->addWidget(hostFactorButton = new QPushButton("Host Factor"),3,0,1,1);
        hostFactorButton->setDisabled(true);
    evaluationLayout->addWidget(hostFactorSpin = new QDoubleSpinBox(),3,1,1,1);
        hostFactorSpin->setRange(0,10);
        hostFactorSpin->setDecimals(1);
        hostFactorSpin->setSingleStep(0.1);
        hostFactorSpin->setAlignment(Qt::AlignCenter);
    evaluationLayout->addWidget(new QLabel("<center>0.0</center>"),3,3,1,1);
    evaluationLayout->addWidget(hostFactorSlider = new QSlider(Qt::Horizontal),3,4,1,1);
        hostFactorSlider->setRange(0,100);
        hostFactorSlider->setValue(33);
    evaluationLayout->addWidget(hostFactorWeightLabel = new QLabel("33%"),3,5,1,1);
    evaluationLayout->addWidget(hostFactorCheck = new QCheckBox(),3,6,1,1);

    connect(hostFactorSlider, SIGNAL(valueChanged(int)), this, SLOT(changeHostFactorWeight(int)));
    connect(hostFactorSlider, SIGNAL(valueChanged(int)), this, SLOT(distributeFactorsWeight()));
    connect(hostFactorCheck, SIGNAL(toggled(bool)), hostFactorSlider, SLOT(setDisabled(bool)));

// result group box
    resultGroup = new QGroupBox("Result:");
    resultLayout = new QGridLayout(resultGroup);

    QFrame *line2 = new QFrame();
    line2->setFrameShape(QFrame::VLine);
    line2->setLineWidth(4);
    resultLayout->addWidget(line2,0,2,2,1);

    resultLayout->addWidget(new QLabel(hostName + " points:"),0,0,1,1);
    resultLayout->addWidget(hostPointsLabel = new QLabel("<b>0.0</b>"),0,1,1,1);
    resultLayout->addWidget(new QLabel(guestName + " points:"),0,3,1,1);
    resultLayout->addWidget(guestPointsLabel = new QLabel("<b>0.0</b>"),0,4,1,1);

    resultLayout->addWidget(new QLabel(hostName + " chance to win:"),1,0,1,1);
    resultLayout->addWidget(hostChanceLabel = new QLabel("<b>33%</b>"),1,1,1,1);
    resultLayout->addWidget(new QLabel(guestName + " chance to win:"),1,3,1,1);
    resultLayout->addWidget(guestChanceLabel = new QLabel("<b>33%</b>"),1,4,1,1);

// put everything in the main layout
    mainLayout->addWidget(evaluationGroup,0,0,1,1);
    QSpacerItem *verticalSpacer = new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Expanding);
    mainLayout->addItem(verticalSpacer,1,0,1,1);
    mainLayout->addWidget(calculateButton = new QPushButton("Calculate"),2,0,1,1);
        calculateButton->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::Minimum);
    mainLayout->addWidget(resultGroup,3,0,1,1);

    connect(calculateButton, SIGNAL(clicked()), this, SLOT(calculateClicked()));
}

MainDialog::~MainDialog()
{

}

void MainDialog::distributeFactorsWeight()
{
    teamValueWeight = teamValueSlider->value() / 100.0;
    statsWeight = statsSlider->value() / 100.0;
    hostFactorWeight = hostFactorSlider->value() / 100.0;
    float fullWeight = teamValueSlider->value() + statsSlider->value() + hostFactorSlider->value();
    if(teamValueCheck->isChecked() && statsCheck->isChecked())
    {
        hostFactorSlider->setDisabled(true);
        hostFactorCheck->setChecked(true);
        return;
    }
    else if(statsCheck->isChecked() && hostFactorCheck->isChecked())
    {
        teamValueSlider->setDisabled(true);
        teamValueCheck->setChecked(true);
        return;
    }
    else if(teamValueCheck->isChecked() && hostFactorCheck->isChecked())
    {
        statsSlider->setDisabled(true);
        statsCheck->setChecked(true);
        return;
    }
    else if(teamValueCheck->isChecked())
    {
        statsSlider->setValue( statsSlider->value() / fullWeight * 100.0 + 0.5 );
        hostFactorSlider->setValue( hostFactorSlider->value() / fullWeight * 100.0 + 0.5 );
    }
    else if(statsCheck->isChecked())
    {
        teamValueSlider->setValue( teamValueSlider->value() / fullWeight * 100.0 + 0.5 );
        hostFactorSlider->setValue( hostFactorSlider->value() / fullWeight * 100.0 + 0.5 );
    }
    else if(hostFactorCheck->isChecked())
    {
        teamValueSlider->setValue( teamValueSlider->value() / fullWeight * 100.0 + 0.5 );
        statsSlider->setValue( statsSlider->value() / fullWeight * 100.0 + 0.5 );
    }
    else
    {
        teamValueSlider->setValue( teamValueSlider->value() / fullWeight * 100.0 + 0.5 );
        statsSlider->setValue( statsSlider->value() / fullWeight * 100.0 + 0.5 );
        hostFactorSlider->setValue( hostFactorSlider->value() / fullWeight * 100.0 + 0.5 );
    }
}

void MainDialog::teamValueClicked()
{
    if(teamValueDialog->exec() == Accepted)
    {
        teamValueSpinHost->setValue(teamValueDialog->getHostValue() / (teamValueDialog->getHostValue() + teamValueDialog->getGuestValue()) * 10.0f);
        teamValueSpinGuest->setValue(teamValueDialog->getGuestValue() / (teamValueDialog->getHostValue() + teamValueDialog->getGuestValue()) * 10.0f);
    }
}

void MainDialog::statsClicked()
{
    if(statsDialog->exec() == Accepted)
    {
        statsSpinHost->setValue( statsDialog->getHostValue() / (statsDialog->getHostValue() + statsDialog->getGuestValue()) * 10.0f );
        statsSpinGuest->setValue( statsDialog->getGuestValue() / (statsDialog->getHostValue() + statsDialog->getGuestValue()) * 10.0f );
    }
}

void MainDialog::calculateClicked()
{
    double hostPoints = teamValueWeight * teamValueSpinHost->value() +
                        statsWeight * statsSpinHost->value() +
                        hostFactorWeight * hostFactorSpin->value();
    double guestPoints = teamValueWeight * teamValueSpinGuest->value() +
                         statsWeight * statsSpinGuest->value();
    double sumPoints = hostPoints + guestPoints;
    hostChance = hostPoints / sumPoints;
    guestChance = guestPoints / sumPoints;

    hostPointsLabel->setText(QString::number(hostPoints,'f',1));
    guestPointsLabel->setText(QString::number(guestPoints,'f',1));
    hostChanceLabel->setText(QString::number(hostChance * 100.0,'f',1) + "%");
    guestChanceLabel->setText(QString::number(guestChance * 100.0,'f',1) + "%");
}

// private slots:
void MainDialog::changeTeamValueWeight(int value)
{
    teamValueWeightLabel->setText(QString::number(value) + "%");
}

void MainDialog::changeStatsWeight(int value)
{
    statsWeightLabel->setText(QString::number(value) + "%");
}

void MainDialog::changeHostFactorWeight(int value)
{
    hostFactorWeightLabel->setText(QString::number(value) + "%");
}
