#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_B

#ifndef CURTAIN_RAIL08B_H
#define CURTAIN_RAIL08B_H

#include "./base08/curtain_base8.h"

class CCurtainRail08b : public CCurtainBase8
{
    Q_OBJECT
    
public:
    explicit CCurtainRail08b(QWidget *parent = 0);

public slots:
    virtual void OnViewDirChange(int);      //显示视角切换
};

#endif // CURTAIN_RAIL08B_H
#endif //USE_RAIL_08_B
