#ifndef QUICK_RAIL12_H
#define QUICK_RAIL12_H

#include "quick_base12.h"


class CQuickRail12 : public CQuickBase12
{
    Q_OBJECT
public:
    explicit CQuickRail12(QWidget *parent = 0);

private:
    void quickPressed00();  //老协议，发送一键
    void quickPressed01();

private slots:
    void quickPressed();

public slots:
    void OnStatusChange(int ,QPushButton *);    //快捷状态改变

};

#endif // QUICK_RAIL12_H
