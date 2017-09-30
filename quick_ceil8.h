#ifndef QUICK_CEIL8_H
#define QUICK_CEIL8_H

#include "quick_base8.h"

class CQuickCeil8 : public CQuickBase8
{
    Q_OBJECT
public:
    explicit CQuickCeil8(QWidget *parent = 0);

public slots:
    void quickPressed();
    void OnStatusChange(int ,QPushButton *);    //快捷状态改变
};

#endif // QUICK_CEIL8_H
