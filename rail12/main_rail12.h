#ifndef MAIN_RAIL12_H
#define MAIN_RAIL12_H

#include "./base12/main_base12.h"


class CMainRail12 : public CMainBase12
{
    Q_OBJECT
    
public:
    explicit CMainRail12(QWidget *parent = 0);

protected:
    virtual void myPopupPosInit();      //部分控件显示位置初始化

public slots:
    virtual void OnViewDirChange(int);      //屏幕显示角度切换
};

#endif // MAIN_RAIL12_H
