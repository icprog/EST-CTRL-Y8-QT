#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_B

#ifndef INFO_RAIL08B_H
#define INFO_RAIL08B_H

#include "./base08/info_base8.h"


class CInfoRail08b : public CInfoBase8
{
    Q_OBJECT
    
public:
    explicit CInfoRail08b(QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *);
    virtual void InfoDisplay();                 //信息显示

public slots:
    virtual void OnViewDirChange(int);      //显示视角切换

};

#endif  //INFO_RAIL08B_H
#endif  //USE_RAIL_08_B
