#ifndef MAIN_RAIL8_H
#define MAIN_RAIL8_H

#include "main_base8.h"


class CMainRail8 : public CMainBase8
{
    Q_OBJECT
    
public:
    explicit CMainRail8(QWidget *parent = 0);

protected:
    virtual void myPopupPosInit();      //部分控件显示位置初始化

};

#endif // MAIN_RAIL8_H
