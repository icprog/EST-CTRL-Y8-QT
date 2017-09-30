#ifndef QUICK_UARM8_H
#define QUICK_UARM8_H

#include "quick_base8.h"

class CQuickUarm8 : public CQuickBase8
{
    Q_OBJECT
public:
    explicit CQuickUarm8(QWidget *parent = 0);

public slots:
    void quickPressed();
    void OnStatusChange(int ,QPushButton *);    //快捷状态改变
};

#endif // QUICK_UARM8_H
