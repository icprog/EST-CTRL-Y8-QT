#ifndef FAST_CEIL10B_H
#define FAST_CEIL10B_H

#include "./base10/fast_base10.h"


class CFastCeil10b : public CFastBase10
{
    Q_OBJECT
public:
    explicit CFastCeil10b(QWidget *parent = 0);
    
signals:
    
public slots:
    virtual void OnStatusChange(int ,QPushButton *); //快捷状态改变
    virtual void OnFastPressed();                 //快捷按钮按下
};

#endif // FAST_CEIL10B_H
