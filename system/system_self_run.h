#ifndef SYSTEM_SELF_RUN_H
#define SYSTEM_SELF_RUN_H

#include "./base/system_base.h"


class CSystemSelfRun : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemSelfRun( QWidget* parent = 0 );

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);

    void keyPressEvent ( QKeyEvent * event );
private:

    QLabel  *edRunInterval;
    QLabel  *edMinuteTotal;
    QLabel  *edMinutePassed;
    QLabel  *lbMinute;

    QFrame *pLine[4];

    CButtonStable *btOk;
    CButtonStable *btFastPosTest;       /*快捷位置-自动运行*/
    CButtonStable *btSoftLimitTest;     /*软件限位-自动运行*/
    CButtonStable *btSwitchLimitTest;   /*硬件限位-自动运行*/
    CButtonStable *btHardLimitTest;     /*机械限位-自动运行-暂不开放*/

    QLabel *lbinfo1;
    QLabel *lbinfo2;
    QLabel *lbinfo3;
    QLabel *lbinfo4;
    QLabel *lbinfo5;
    QLabel *lbinfo6;
    QLabel *lbinfo7;
    QLabel *lbinfo8;

    int m_iAutoRunSel;                     /*当前选择的自运行方式*/
public slots:
    void OnSelfRunPressed();
    void OnRunModePressed();

    bool eventFilter(QObject *, QEvent *);

};

#endif //SYSTEM_SELF_RUN_H
