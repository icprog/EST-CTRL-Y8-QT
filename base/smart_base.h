#ifndef SMART_BASE_H
#define SMART_BASE_H

#include <QWidget>

#include "button_stable.h"
#include "./system/system_defines.h"

#define SMART_RUN_MAX       (20)

#define SMART_NULL              (0)        /*stand finished*/
#define SMART_STAND             (1)        /*stand finished*/
#define SMART_TABLE             (2)         /*table finished*/
#define SMART_STAND_SLASH       (4)        /*stand finished*/
#define SMART_TABLE_SLASH       (8)         /*table finished*/
#define SMART_STAND_TABLE       (16)         /*table finished*/

#define SMART_STATE_FREE        (1)         /*empty*/
#define SMART_STATE_PARAM_SEND  (2)         /*sending param*/
#define SMART_STATE_PARAM_WAIT  (4)         /*sending param*/
#define SMART_STATE_CMD_SEND    (8)         /*sending param*/
#define SMART_STATE_CMD_WAIT    (16)         /*sending param*/
#define SMART_STATE_SLASH_SEND  (32)         /*sending param*/
#define SMART_STATE_SLASH_WAIT  (64)         /*sending param*/

#define M_CUR_BUF_MAX   10


class CSmartBase : public QWidget
{
    Q_OBJECT
    
public:
    explicit CSmartBase(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *event);

    void SendCmdKey(int);               //发送给下位机的命令

protected:
    QTimer  * timerAutoRun;         //延时定时器，用于自运行控制
    int m_iSmartRun[SMART_RUN_MAX]; //自运行时的自动序列
    int m_iSmartIndex;              //记录当前自运行的序号
    int m_iSmartRunMax;             //自运行记录的数量
    int m_iTimerCounter;            //时间记录,用于自运行

    int m_iSmartChannel;            //快捷按钮通道,
    int m_iSmartState;          //快捷控制状态机
    int m_iSmartTarget;         //快捷位置目标

    int mSmartMax;                              //允许的最大Smart数量
    CButtonStable * pBtnGroup[SYS_SMART_MAX];   //Smart按钮
    unsigned short m_codeSmart[SYS_SMART_MAX];     //一键动作代码

    virtual void OnSelfRunControl();
    virtual int SmartCmdWait();

    virtual void OnSelfRunCtrlSoft();
    virtual void OnSelfRunCtrlHard();
    virtual void OnSelfRunCtrlMach();

    int m_iCtrlSoftStat;
    unsigned short mCurBuf[M_CUR_BUF_MAX];

private slots:
    void OnSmartFresh();

public slots:
    virtual void OnStatusChange(int);       //Smart状态切换信号槽，用于10寸屏的消息回馈
    virtual void OnSmartPressed();          //Smart按钮按下信号槽
    virtual void OnSmartPressed(int);          //Smart按钮按下信号槽
    virtual void OnSmartChange(int mPos);   //
    virtual void OnKeyPressed(int);         //有物理按键、液晶按键按下
    virtual void OnViewDirChange(int);      //显示视角切换

signals:
    void RunStatusChange(int,QPushButton*);         //状态切换信号
    void PopupHide(QWidget* );                      //隐藏自己
    void InfoMsgCtrl(int , int,void * param = 0);
    void ComKeyCommand(unsigned short );    //for motion simulate
};


#define SELF_RUN_SOFT_00  0
#define SELF_RUN_SOFT_01  1
#define SELF_RUN_SOFT_02  2
#define SELF_RUN_SOFT_03  3
#define SELF_RUN_SOFT_04  4
#define SELF_RUN_SOFT_05  5
#define SELF_RUN_SOFT_06  6
#define SELF_RUN_SOFT_07  7
#define SELF_RUN_SOFT_08  8
#define SELF_RUN_SOFT_09  9
#define SELF_RUN_SOFT_10  10
#define SELF_RUN_SOFT_11  11
#define SELF_RUN_SOFT_12  12
#define SELF_RUN_SOFT_13  13
#define SELF_RUN_SOFT_14  14
#define SELF_RUN_SOFT_15  15
#define SELF_RUN_SOFT_16  16
#define SELF_RUN_SOFT_17  17
#define SELF_RUN_SOFT_18  18
#define SELF_RUN_SOFT_19  19
#define SELF_RUN_SOFT_20  20
#define SELF_RUN_SOFT_21  21
#define SELF_RUN_SOFT_22  22
#define SELF_RUN_SOFT_23  23

#endif // SMART_BASE_H
