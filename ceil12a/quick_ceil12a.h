#include "./base12/quick_base12.h"
#ifdef USE_CEIL_12_A

#ifndef QUICK_CEIL_12A_H
#define QUICK_CEIL_12A_H


class CQuickCeil12a : public CQuickBase12
{
    Q_OBJECT
public:
    explicit CQuickCeil12a(QWidget *parent = 0);

protected:
    virtual void quickBtnInit(uchar);            //按钮初始化


public slots:
    virtual void quickPressed();
    virtual void OnStatusChange(int );    //快捷状态改变

};

#endif  //QUICK_CEIL_12A_H
#endif  //USE_CEIL_12_A
