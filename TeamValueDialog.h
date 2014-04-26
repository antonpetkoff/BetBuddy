#ifndef TEAMVALUEDIALOG_H
#define TEAMVALUEDIALOG_H

#include "TeamValueWidget.h"

#include <QDialog>
#include <QGridLayout>
#include <QDialogButtonBox>

class TeamValueDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TeamValueDialog(QWidget *parent = 0);
    ~TeamValueDialog();
    float getHostValue() const;
    float getGuestValue() const;

private:
    QGridLayout *mainLayout;
    TeamValueWidget *home;
    TeamValueWidget *away;
    QDialogButtonBox *pushExit;
};

#endif // TEAMVALUEDIALOG_H
