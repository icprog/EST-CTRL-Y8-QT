#ifndef QUICK_BASE10_H
#define QUICK_BASE10_H

#include "quick_base.h"


class CQuickBase10 : public CQuickBase
{
    Q_OBJECT
public:
    explicit CQuickBase10(QWidget *parent = 0);

private slots:
    virtual void quickPressed();
    virtual void quickReleased();

public slots:
    virtual void OnViewDirChange(int);
    void OnKeyLongPress();                      //长按按键触发
};

#endif // QUICK_BASE10_H
