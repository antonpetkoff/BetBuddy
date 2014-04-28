#ifndef STATSDIALOG_H
#define STATSDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QString;
class QSpinBox;
class QPushButton;
class QLabel;
class StatsWidget;
class QDialogButtonBox;
QT_END_NAMESPACE

class StatsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatsDialog(const QString & host = "Host Team",
                         const QString & guest = "Guest Team",
                         QWidget *parent = 0);
    ~StatsDialog();

    double getHostValue();
    double getGuestValue();
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
