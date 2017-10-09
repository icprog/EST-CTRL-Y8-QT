#ifndef INFO_BASE_H
#define INFO_BASE_H

#include <QWidget>
#include <QLabel>

#include "./system/system_defines.h"

class CInfoBase : public QWidget
{
    Q_OBJECT
public:
    explicit CInfoBase(QWidget *parent = 0);

    int m_iLimitMask;               //限位屏蔽，不同的系统限位数量不同，设置不同的屏蔽

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *);

    virtual void InfoDisplay();                 //信息显示
    virtual void InfoMonitor();                 //信息监视

private:
    void InfoAdd(int msgCode,void * param = 0);         //添加信息
    void InfoFresh(int msgCode,void * param = 0);       //刷新信息
    void InfoDel(int msgCode);                          //删除信息

    int     GetInfoIcon(int,int);       //获取信息的图标
    QString GetInfoMsg(int);            //获取信息的内容
    void InfoLevelFresh();              //刷新信息等级记录

protected:
    int     m_iMsgCode[INFO_SCROLL_MAX];    //代码，所有信息代码都在此存储
    int     m_iMsgPicture[INFO_SCROLL_MAX]; //图片
    QString m_iMsgInfo[INFO_SCROLL_MAX];    //内容

    int m_iLevelPtr;                        //等级指针，指向目前需要显示的等级
    int m_iMsgNum;                          //信息数量
    int m_iMsgDispInx;                      //显示指针
    int m_iRunStatus;                       //运行状态

    QString * pmMsgIcon[INFO_PIC_MAX];      //图标
    int     m_iMsgLevel[INFO_PIC_MAX];      //等级

    QTimer * timerInfoFresh;                //刷新时钟

    QLabel *lbMsgInfo;
    QFrame *lbMsgIcon;

    int m_iPosiCaliValid;                   //位置校正数据是否正确

public slots:
    virtual void OnInfoMsgCtrl(int ctrl,int msgCode,void * msgParam = 0);
    virtual void OnInfoFresh();     //刷新提示信息
    virtual void OnViewDirChange(int);      //显示视角切换
signals:

    void ViewChange(int);           //切换视图信号，主要用于系统到期检测
    void RunStatusChange(int);      //运行状态切换
};

#endif // INFO_BASE_H
