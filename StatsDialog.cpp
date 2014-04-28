#include "StatsDialog.h"

#include "StatsWidget.h"
#include <QString>
#include <QGridLayout>
#include <QGroupBox>
#include <QSpinBox>
#include <QSpacerItem>
#include <QLabel>
#include <QPushButton>
#include <QDialogButtonBox>

StatsDialog::StatsDialog(const QString & host, const QString & guest, QWidget *parent) :
    QDialog(parent), hostName(host), guestName(guest)
{
    this->resize(800,540);
    this->setWindowTitle("Previous Matches Statistics");
    QGridLayout *dialogLayout = new QGridLayout(this);

    editButton = new QPushButton("Edit");
    editButton->setDisabled(true);
    calculateButton = new QPushButton("Calculate");
    homeValue = new QLabel("0");
    awayValue = new QLabel("0");

    spinNumMatches = new QSpinBox();
    spinNumMatches->setMinimum(3);
    spinNumMatches->setMaximum(15);
    spinNumMatches->setValue(5);
    spinNumMatches->setAlignment(Qt::AlignHCenter);

    QGroupBox *groupChoice = new QGroupBox("Interface");
    QHBoxLayout *firstRow = new QHBoxLayout(groupChoice);
    firstRow->addItem(new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Minimum));
    firstRow->addWidget(new QLabel("Consider last "));
    firstRow->addWidget(spinNumMatches);
    firstRow->addWidget(new QLabel(" matches."));
    firstRow->addWidget(editButton);
    firstRow->addWidget(calculateButton);
    firstRow->addItem(new QSpacerItem(10,10,QSizePolicy::Expanding,QSizePolicy::Minimum));

    QGroupBox *groupResult = new QGroupBox("Result");
    QGridLayout *resultLayout = new QGridLayout(groupResult);
    resultLayout->addWidget(new QLabel(hostName + " points:"),0,0,1,1);
    resultLayout->addWidget(homeValue,0,1,1,1);
    resultLayout->addWidget(new QLabel(guestName + " points:"),1,0,1,1);
    resultLayout->addWidget(awayValue,1,1,1,1);

    QGroupBox *groupHome = new QGroupBox("Previous Matches of " + hostName);
    QGridLayout *layoutHome = new QGridLayout(groupHome);
    home = new StatsWidget(5,groupHome);
    layoutHome->addWidget(home,0,0,1,1);

    QGroupBox *groupAway = new QGroupBox("Previous Matches of " + guestName);
    QGridLayout *layoutAway = new QGridLayout(groupAway);
    away = new StatsWidget(5,groupAway);
    layoutAway->addWidget(away,0,0,1,1);

    dialogLayout->addWidget(groupChoice,0,0,1,1);
    dialogLayout->addWidget(groupResult,0,1,1,1);
    dialogLayout->addWidget(groupHome,1,0,1,1);
    dialogLayout->addWidget(groupAway,1,1,1,1);
    dialogLayout->addWidget(buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel, Qt::Horizontal),2,1,1,1);

    connect(spinNumMatches, SIGNAL(valueChanged(int)), this, SLOT(numberOfMatchesChanged(int)));
    connect(editButton, SIGNAL(clicked()), this, SLOT(editClicked()));
    connect(calculateButton, SIGNAL(clicked()), this, SLOT(calculateClicked()));

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

StatsDialog::~StatsDialog()
{
}

double StatsDialog::getHostValue()
{
    return home->calculateValue();
}

double StatsDialog::getGuestValue()
{
    return away->calculateValue();
}

void StatsDialog::numberOfMatchesChanged(int value)
{
    if(value == home->getNumberOfMatches())
        editButton->setDisabled(true);
    else editButton->setDisabled(false);
}

void StatsDialog::editClicked()
{
    editButton->setDisabled(true);
    home->editMatchRows(spinNumMatches->value());
    away->editMatchRows(spinNumMatches->value());
}

void StatsDialog::calculateClicked()
{
    homeValue->setNum(home->calculateValue());
    awayValue->setNum(away->calculateValue());
}
