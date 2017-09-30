#ifndef CURTAIN_BASE12_H
#define CURTAIN_BASE12_H

#include "curtain_base.h"

class CCurtainBase12 : public CCurtainBase
{
    Q_OBJECT
    
public:
    explicit CCurtainBase12(QWidget *parent = 0);

public slots:
    virtual void OnCurtainSwitch();
    virtual void OnCurtainStateFresh();
    virtual void OnViewDirChange(int);      //显示视角切换
};

#endif // CURTAIN_BASE12_H
