#ifndef QUICK_BASE12_H
#define QUICK_BASE12_H

#include "quick_base.h"


class CQuickBase12 : public CQuickBase
{
    Q_OBJECT
public:
    explicit CQuickBase12(QWidget *parent = 0);

signals:

private slots:
    void quickReleased();
    void OnKeyLongPress();                      //长按按键触发

public slots:
    virtual void OnViewDirChange(int);
};

#endif // QUICK_BASE12_H
