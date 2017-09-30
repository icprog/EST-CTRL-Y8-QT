#ifndef SYSTEM_CONFIRM2_H
#define SYSTEM_CONFIRM2_H

#include "system_base.h"


class CSystemConfirm2 : public CSystemBase
{
    Q_OBJECT
public:
    CSystemConfirm2( QWidget* parent = 0);

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:

    QList <QLabel*> arrLabel;

    QLabel *stinfo;
    QLabel *edPassword;

    QFrame *mLine1;

    CButtonStable *btOk;
    CButtonStable *btContinueUse;

    int pay_flag;

    unsigned int PeriodPassx(unsigned int password);

public slots:
    void click();
    bool eventFilter(QObject *, QEvent *);
    void OnEmergencyUse();
};

#endif //SYSTEM_CONFIRM2_H
