#ifndef SYSTEM_LIGHT_CURTAIN_H
#define SYSTEM_LIGHT_CURTAIN_H

#include <QTimer>
#include "system_base.h"


#define LC_EDIT_MAX 1
#define SYS_LIGHT_CURTAIN_FRESH     500
#define LC_MAX_LENGTH   5
#define LC_INDEX_HEIGHT_BASE    0
#define LC_CMD_SAVE 1
#define LC_CMD_ON    2
#define LC_CMD_OFF   3
#define LC_CMD_FRESH   4

class CSystemLightCurtain: public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemLightCurtain(QWidget* parent = 0 );

protected:

    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *watched, QEvent *event);
    void keyPressEvent ( QKeyEvent * event );

public:
    int m_iLightCurtainState;       //on == 1 ; off == 0
    int m_iLightCurtainHold;       //on == 1 ; off == 0
    int m_iLightCurtainShow;       //on == 1 ; off == 0

    int m_iLCHeightBase;
    int m_iLCSample;
    int m_iLCHumanHeight;
    int m_iLCChestHeight;

private:

    CButtonStable* btSave;                          //save
    CButtonStable *btnLightCurtainOn;       //open
    CButtonStable *btnLightCurtainOff;      //close
    CButtonStable *btnLightCurtainHold;      //hold the state every start up
    CButtonStable *btnLightCurtainShow;      //Display on the main Page//8inch rail only

    QLabel * pEditArr[LC_EDIT_MAX];            //光幕基础高度,input,display
    QLabel * staticHeightBase;          //光幕基础高度,text

    QLabel * staticSampleValue;         //光幕高度采样数值
    QLabel * staticHumanHeight;      //
    QLabel * staticChestHeight;      //
    QLabel * staticMsgReceive;      //

    QLabel * staticCM_0;      //
    QLabel * staticCM_1;      //
    QLabel * staticCM_2;      //

    QLabel * strSampleValue;         //光幕高度采样数值
    QLabel * strHumanHeight;      //
    QLabel * strChestHeight;      //

    QLabel * strMessage;      //显示消息提示

    QTimer *m_tmLightCurtain;//定时器，定时通信，暂定200ms间隔

    int m_iBaseHeightFreshEnable;   //fresh base height or not

public slots:
    void OnBtnSaveData();           //保存光幕基础高度数值
    void OnBtnExit();               //退出本界面
    void OnBtnCtrl();               //关闭,开启,保持,显示操作

    void OnTimerLightCurtain();//定时器
};

#endif //SYSTEM_LIGHT_CURTAIN_H
