#include "TeamValueDialog.h"

#include "TeamValueWidget.h"
#include <QGridLayout>
#include <QDialogButtonBox>

TeamValueDialog::TeamValueDialog(QWidget *parent) :
    QDialog(parent)
{
    this->setMinimumSize(800,500);
    mainLayout = new QGridLayout(this);
    home = new TeamValueWidget();
    away = new TeamValueWidget();
    pushExit = new QDialogButtonBox(Qt::Horizontal);
    pushExit->setStandardButtons(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    mainLayout->addWidget(home,0,0,1,1);
    mainLayout->addWidget(away,0,1,1,1);
    mainLayout->addWidget(pushExit,1,0,1,2);

    connect(pushExit, SIGNAL(accepted()), this, SLOT(accept()));
    connect(pushExit, SIGNAL(rejected()), this, SLOT(reject()));
}

TeamValueDialog::~TeamValueDialog()
{
}

float TeamValueDialog::getHostValue() const
{
    return home->avarageTeamRating;
}

float TeamValueDialog::getGuestValue() const
{
    return away->avarageTeamRating;
}
