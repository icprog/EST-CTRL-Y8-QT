#ifndef SMART_BASE12_H
#define SMART_BASE12_H

#include "smart_base.h"


class CSmartBase12 : public CSmartBase
{
    Q_OBJECT

public:
    explicit CSmartBase12(QWidget *parent = 0);

protected:
    void mousePressEvent(QMouseEvent *event);
    QTimer * timerMenuMsgWaig;
    QTimer * timerSmartRun;

    int m_iWaitCounter;      /*统计发送位置命令的时间*/

    void OnSelfRunControl();    //支持重载的自动运行控制
    void ReloadSmartData(int);  //发送当前快捷目标参数
    bool SmartParamWait();      //等待目标参数发送完成
    void SmartCmdSend();        //根据通道，发送一键动作指令
    int SmartCmdWait();         //等待一键动作执行完毕,返回1：当前命令完成，有后续命令，0：当前命令完成，无后续命令，-1：当前命令未完成
    void SmartSlashSend();      //发送斜线命令
    int SmartSlashWait();       //等待斜线命令执行完毕
    int SmartChannelGet();      //获取当前有效的通道
    void SmartCancel();         //根据系统状态，取消一键动作

public slots:
    void OnMenuMsgWait();
    void OnTimerSmartRun();
    void OnKeyPressed(int);

public slots:
    virtual void OnViewDirChange(int);  //显示视角切换
};

#endif // SMART_BASE12_H
