#ifndef QUICK_BASE8_H
#define QUICK_BASE8_H

#include "./base/quick_base.h"


class CQuickBase8 : public CQuickBase
{
    Q_OBJECT
public:
    explicit CQuickBase8(QWidget *parent = 0);
    
signals:
    
private slots:
    void quickReleased();
    void OnKeyLongPress();                      //长按按键触发

};

#endif // QUICK_BASE8_H
