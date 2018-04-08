#include "./base12/main_base12.h"

#ifdef USE_CEIL_12_A

#ifndef MAIN_CEIL_12A_H
#define MAIN_CEIL_12A_H

class CMainCeil12a : public CMainBase12
{
    Q_OBJECT
    
public:
    explicit CMainCeil12a(QWidget *parent = 0);

protected:
    virtual void myPopupPosInit();      //部分控件显示位置初始化

};

#endif  //MAIN_CEIL_12A_H
#endif  //USE_CEIL_12_A
