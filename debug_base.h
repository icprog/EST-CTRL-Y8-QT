#ifndef DEBUG_BASE_H
#define DEBUG_BASE_H

#include "system_base.h"

#define DEBUG_CHANNEL_MAX   ( 6 )                       /*调试页面电机通道数*/
#define DEBUG_BTN_MAX       ( 2 * DEBUG_CHANNEL_MAX )    /*调试页面，电机控制按钮数量*/
#define DEBUG_LIMIT_MAX     ( 18 )    /*最大限位数量，包含电机用12个，其他6个*/


class CDebugBase : public CSystemBase
{
    Q_OBJECT
public:
    explicit CDebugBase(QWidget *parent = 0);
    
protected:
    void SendCmdKey(int);               //发送给下位机的命令

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void keyPressEvent( QKeyEvent * );

    int m_iMotorMax;                //支持调试的最大电机数量
    int m_iBtnIdx;                  //当前高亮显示的按钮编号

    QFrame  * pLineAry[3];
    unsigned long m_lLimitBuf;      /*由于限位刷新很耗费时间，因此增加缓冲，如果实际数据与缓冲相同，则不刷新显示*/

    QTimer          * timerDebugRefresh;
    unsigned short bufComMessage[128];

    unsigned short pKeycodePressed[DEBUG_BTN_MAX];
    unsigned short pKeycodeReleased[DEBUG_BTN_MAX];
    QLabel      * pLabelAd[DEBUG_CHANNEL_MAX];
    QLabel      * pLimitText[DEBUG_LIMIT_MAX];
    QFrame      * pLimitFrame[DEBUG_LIMIT_MAX];
    CButtonStable * pBtnGroup[DEBUG_BTN_MAX];


    virtual void UpdateSampleData();
    
public slots:
    virtual void OnDebugFresh();
    virtual void OnDebugPressed();
    virtual void OnDebugReleased();
};

#endif // DEBUG_BASE_H
