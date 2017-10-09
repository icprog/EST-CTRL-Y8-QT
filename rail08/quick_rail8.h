#ifndef QUICK_RAIL8_H
#define QUICK_RAIL8_H

#include "./base08/quick_base8.h"


class CQuickRail8 : public CQuickBase8
{
    Q_OBJECT
public:
    explicit CQuickRail8(QWidget *parent = 0);
    
private:
    void quickPressed00();  //老协议，发送一键
    void quickPressed01();

private slots:
    void quickPressed();
    
public slots:
    void OnStatusChange(int ,QPushButton *);    //快捷状态改变

};

#endif // QUICK_RAIL8_H
