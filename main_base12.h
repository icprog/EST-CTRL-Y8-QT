#ifndef MAIN_BASE12_H
#define MAIN_BASE12_H

#include "main_base.h"


class CMainBase12 : public CMainBase
{
    Q_OBJECT

public:
    explicit CMainBase12(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);   //显示
    void hideEvent(QHideEvent *);   //隐藏

    virtual void myViewInit();      //视图初始化
    virtual void mySceneInit();     //场景初始化
    virtual void myPopupPosInit();  //弹出框位置初始化

    int m_iDirRight[VIEW_DIR_MAX][VIEW_DIR_MAX];
protected:
    QGraphicsView   * viewKey;      //用于12寸系统的屏幕按键
    QGraphicsView   * viewTitle;    //用于12寸系统的屏幕标题
    QGraphicsView   * viewQuick;    //用于12寸系统的3个一键位
    QGraphicsView   * viewNet;      //用于12寸系统的网络图标显示
    QGraphicsView   * viewPower;    //用于12寸系统的程序关闭按钮，一般用于PAD上显示
    QGraphicsView   * viewSim;      //用于运动模拟，测试使用。
    QGraphicsView   * viewCurtain;  //用于光幕开关按钮
    QGraphicsView   * viewNotify;  //用于运动模拟，测试使用。

public slots:

    virtual void OnPopupShow(int popIdx);   //弹出界面控制
    virtual void OnPopupHide(QWidget *);    //弹出界面消隐
    virtual void OnViewDirChange(int);      //屏幕显示角度切换
    virtual void OnViewChange(int);         //显示视图变更
};


#endif // MAIN_BASE12_H
