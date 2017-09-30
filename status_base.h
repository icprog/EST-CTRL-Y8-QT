#ifndef STATUS_BASE_H
#define STATUS_BASE_H

#include <QWidget>
#include <QLabel>
#include <QTimer>
#include <QLCDNumber>
#include "system_defines.h"

//1.显示位置信息
//2.根据角度数据判断是否需要切换显示视角

class CStatusBase : public QWidget
{
    Q_OBJECT
    
public:
    explicit CStatusBase(QWidget *parent = 0);
    
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent*);

protected:
    QFrame * lbIcon[SYS_MOTOR_MAX];     //用于显示标志图标
    QLCDNumber * lcd[SYS_MOTOR_MAX];    //用于显示位置数据

    QTimer * timerStatusFresh;          //用于刷新显示数据
    int m_iViewDir;

signals:
    void ViewDirChange(int);            //显示视角切换信号

public slots:
    virtual void OnStatusFresh();       //显示位置信息刷新
    virtual void OnViewDirChange(int);  //显示视角切换
};

#endif // STATUS_BASE_H
