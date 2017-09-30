#ifndef SYSTEM_CONFIRM_H
#define SYSTEM_CONFIRM_H

#include "system_base.h"


class CSystemConfirm : public CSystemBase
{
    Q_OBJECT
public:
    CSystemConfirm( QWidget* parent = 0);

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:

    QLabel *label0;
    QLabel *label1;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
    QLabel *label5;
    QLabel *label6;
    QLabel *label7;
    QLabel *label8;
    QLabel *label9;
    QLabel *label10;
    QLabel *label11;
    QLabel *label12;
    QLabel *label13;
    QLabel *label14;

    QLabel *label20;
    QLabel *label21;
    QLabel *label22;
    QLabel *label23;
    QLabel *label24;
    QLabel *stinfo;

    QFrame *mLine1;
    CButtonStable *btOk;
    CButtonStable *btContinueUse;

    QLabel *edPassword;

    int pay_flag;

    unsigned int PeriodPassx(unsigned int password);
    int transtoword(char* p);

public slots:
    void click();
    bool eventFilter(QObject *, QEvent *);
    void OnEmergencyUse();
};

#endif //SYSTEM_CONFIRM_H
