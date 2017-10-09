#ifndef MAIN_BASE10_H
#define MAIN_BASE10_H

#include "./base/main_base.h"


//1.角度切换控制
//2.弹出框显示与消失
//3.可视控件位置初始化
class CMainBase10 : public CMainBase
{
    Q_OBJECT
    
public:
    explicit CMainBase10(QWidget *parent = 0);

protected:

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void myViewInit();              //视图对象初始化
    void mySceneInit();             //场景对象初始化

protected:
    virtual void myPopupPosInit();  //基础视图对象位置初始化

                                    //当右侧安装时，动画区域的角度切换参数
    int m_iDirRight[VIEW_DIR_MAX][VIEW_DIR_MAX];

public slots:

    void OnPopupShow(int popIdx);   //弹出框显示
    void OnPopupHide(QWidget *);    //弹出框隐藏
    void OnViewDirChange(int);      //显示视角切换
    virtual void OnViewChange(int);         //显示视图变更
};

#endif // MAIN_BASE10_H
