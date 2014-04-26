#include "StatsWidget.h"

StatsWidget::StatsWidget(int matches, QWidget *parent) :
    QWidget(parent), numberOfMatches(matches)
{
    mainLayout = new QGridLayout(this);
    statsLayout = new QGridLayout();

    statsLayout->addWidget(new QLabel("Match"),0,0,1,1);
    statsLayout->addWidget(new QLabel("Venue"),0,1,1,1);
    statsLayout->addWidget(new QLabel("Opponent Strength"),0,3,1,1);
    statsLayout->addWidget(new QLabel("Host goals vs. Guest goals"),0,4,1,2);

    for(int i=0;i < numberOfMatches;i++)
        addMatchRow(i);

    mainLayout->addLayout(statsLayout,1,0,1,1);
    mainLayout->addItem(new QSpacerItem(10,10,QSizePolicy::Minimum,QSizePolicy::Expanding),2,0,1,1);
}

void StatsWidget::editMatchRows(int value)
{
    if(value > numberOfMatches)
        for(int i = numberOfMatches;i < value;i++)
            addMatchRow(i);

    if(value < numberOfMatches)
        for(int row = numberOfMatches - 1;row > value - 1;row--)
        {
            for(int col=0;col < 6;col++)
                if(statsLayout->itemAtPosition(row+1,col))
                    delete (statsLayout->itemAtPosition(row+1,col))->widget();
            venue.pop_back();
            opponent.pop_back();
            hostGoals.pop_back();
            guestGoals.pop_back();
        }
    numberOfMatches = value;
}

void StatsWidget::addMatchRow(int i)
{
    statsLayout->addWidget(new QLabel(QString::number(i+1) + ": "),i+1,0,1,1);

    venue.insert(i, new QComboBox());
    venue[i]->addItem("At Home");
    venue[i]->addItem("Away");
    statsLayout->addWidget(venue[i],i+1,1,1,1);

    statsLayout->addWidget(new QLabel(" vs. "),i+1,2,1,1);

    opponent.insert(i, new QSpinBox());
    opponent[i]->setRange(1,10);
    opponent[i]->setValue(5);
    opponent[i]->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    statsLayout->addWidget(opponent[i],i+1,3,1,1);

    hostGoals.insert(i, new QSpinBox());
    hostGoals[i]->setAlignment(Qt::AlignHCenter);
    statsLayout->addWidget(hostGoals[i],i+1,4,1,1);

    guestGoals.insert(i, new QSpinBox());
    guestGoals[i]->setAlignment(Qt::AlignHCenter);
    statsLayout->addWidget(guestGoals[i],i+1,5,1,1);
}

double StatsWidget::calculateValue()
{
    double teamValue = 0;

    for(int i=0;i<numberOfMatches;i++)
    {
        if(venue[i]->currentText() == "At Home")
        {
            int goalDifference = hostGoals[i]->value() - guestGoals[i]->value();
            if(goalDifference > 0)          teamValue += 3 * factor(opponent[i]->value());
            else if(goalDifference == 0)    teamValue += 1 * factor(opponent[i]->value());
            else if(goalDifference < 0)
            {
            }
        }
        else if(venue[i]->currentText() == "Away")
        {
            int goalDifference = guestGoals[i]->value() - hostGoals[i]->value();
            if(goalDifference > 0)          teamValue += guestBonus + 3.0f * factor(opponent[i]->value());
            else if(goalDifference == 0)    teamValue += guestBonus + factor(opponent[i]->value());
            else if(goalDifference < 0)
            {
            }
        }
    }

    return teamValue;
}

double StatsWidget::factor(int teamQuality)
{
    switch(teamQuality)
    {
        case 1: return 0.50;
        case 2: return 0.60;
        case 3: return 0.70;
        case 4: return 0.80;
        case 5: return 0.90;
        case 6: return 1.10;
        case 7: return 1.20;
        case 8: return 1.30;
        case 9: return 1.40;
        case 10: return 1.50;
        default: return 1.00;
    }
}
