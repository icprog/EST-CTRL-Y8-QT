#ifndef CURTAIN_BASE10_H
#define CURTAIN_BASE10_H

#include "./base/curtain_base.h"

class CCurtainBase10 : public CCurtainBase
{
    Q_OBJECT
    
public:
    explicit CCurtainBase10(QWidget *parent = 0);
    

public slots:
    virtual void OnViewDirChange(int);      //显示视角切换
};

#endif // CURTAIN_BASE10_H
