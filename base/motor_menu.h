#ifndef MOTOR_MENU_H
#define MOTOR_MENU_H

#include "./base/system_base.h"

#define MENU_MOTION_WID_MAX         ( 9 )
#define MENU_MOTION_IDX0            ( 0 )
#define MENU_MOTION_IDX1            ( 1 )
#define MENU_MOTION_IDX2            ( 2 )
#define MENU_MOTION_IDX3            ( 3 )
#define MENU_MOTION_IDX4            ( 4 )
#define MENU_MOTION_IDX5            ( 5 )
#define MENU_MOTION_IDX6            ( 6 )
#define MENU_MOTION_IDX7            ( 7 )
#define MENU_MOTION_IDX8            ( 8 )


class CMotorMenu : public CSystemBase
{
    Q_OBJECT
    
public:
    explicit CMotorMenu(unsigned short mPlatform,QWidget *parent = 0);
    
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:
    QLabel *label_2;

    QWidget * m_iWidArray[MENU_MOTION_WID_MAX];
    CButtonStable * pBtnGroup[MENU_MOTION_WID_MAX];

    CButtonStable *pBtnSoftLimitSet;

    void InitMenuMotion(unsigned short mPf);

    int m_iPlatform;            //平台指针
    int m_iBtnCount;          //按钮数量
public slots:
    void OnButtonClick();
    void OnSoftLimitSet();
};

#endif // MOTOR_MENU_H
