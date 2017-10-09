#ifndef SYSTEM_SPEED_H
#define SYSTEM_SPEED_H

#include <QTimer>
#include "./base/system_base.h"

#define SPEED_BTN_MAX                   (16)
#define SPEED_BTN_SLOW                  (8)
#define SPEED_MAX_LENGTH                (2)


class CSystemSpeed : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemSpeed(unsigned short mPlatform, QWidget* parent = 0 );

protected:

    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);

    void keyPressEvent ( QKeyEvent * event );

private:
    int mMotorMax;
    QTimer      * timerSpeedFresh;
    QLabel      * pEditSpeed[SPEED_BTN_SLOW];
    QLabel      * pEditMax[SPEED_BTN_SLOW];
    QFrame      * pFrameLine[SPEED_BTN_SLOW];
    QLabel      * pLabelGroup[SPEED_BTN_SLOW];
    QLabel      * pLabel[SPEED_BTN_SLOW];
    QLabel      * lbSave;
    CButtonStable* btSave;

    void InitSpeedCfg(unsigned short mPf);

public slots:
    void OnSpeedFresh();
    void OnSpeedClickIndex();
    void OnSpeedClickSave();
    bool eventFilter(QObject *, QEvent *);
};

#endif //SYSTEM_SPEED_H
