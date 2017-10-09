#ifndef MAIN_UARM8_H
#define MAIN_UARM8_H

#include "./base08/main_base8.h"

//初始化液晶屏按键和状态栏位置

class CMainUarm8 : public CMainBase8
{
    Q_OBJECT
    
public:
    explicit CMainUarm8(QWidget *parent = 0);

protected:
    virtual void myPopupPosInit();  //位置初始化

};

#endif // MAIN_UARM8_H
