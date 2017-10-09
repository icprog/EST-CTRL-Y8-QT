#ifndef FAST_BASE_H
#define FAST_BASE_H

#include <QWidget>
#include <QLabel>

#include "button_stable.h"

class CFastBase : public QWidget
{
    Q_OBJECT
    
public:
    explicit CFastBase(QWidget *parent = 0);
    
protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);

protected:

    QLabel      *lbFastPosition;        //快捷消息反馈
    CButtonStable *btMotionSmart;       //快捷触发按钮

public slots:
    virtual void OnStatusChange(int ,QPushButton *); //快捷状态改变
    virtual void OnFastPressed();                 //快捷按钮按下
    virtual void OnViewDirChange(int);      //显示视角切换

signals:
    void SmartChange(int); //快捷位置变更
    void ViewChange(int );                  //视图切换
    void PopupShow(int );                   //弹出快捷按钮
};

#endif // FAST_BASE_H
