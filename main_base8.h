#ifndef MAIN_BASE8_H
#define MAIN_BASE8_H

#include "main_base.h"


class CMainBase8 : public CMainBase
{
    Q_OBJECT
    
public:
    explicit CMainBase8(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);   //显示
    void hideEvent(QHideEvent *);   //隐藏

    virtual void myViewInit();      //视图初始化
    virtual void mySceneInit();     //场景初始化
    virtual void myPopupPosInit();  //弹出框位置初始化

protected:
    QGraphicsView   * viewKey;      //用于8寸系统的屏幕按键
    QGraphicsView   * viewTitle;    //用于8寸系统的屏幕标题

public slots:

    virtual void OnPopupShow(int popIdx);   //弹出界面控制
    virtual void OnPopupHide(QWidget *);    //弹出界面消隐
    virtual void OnViewDirChange(int);      //屏幕显示角度切换
    virtual void OnViewChange(int);         //显示视图变更
};


#endif // MAIN_BASE8_H
