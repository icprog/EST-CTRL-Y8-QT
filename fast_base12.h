#ifndef FAST_BASE12_H
#define FAST_BASE12_H

#include "fast_base.h"


class CFastBase12 : public CFastBase
{
    Q_OBJECT
    
public:
    explicit CFastBase12(QWidget *parent = 0);

public slots:
    virtual void OnFastPressed();                 //快捷按钮按下
    virtual void OnStatusChange(int ,QPushButton *); //快捷状态改变
    virtual void OnViewDirChange(int);      //显示视角切换

protected:

};

#endif // FAST_BASE12_H
