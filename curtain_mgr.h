#ifndef CURTAIN_MGR_H
#define CURTAIN_MGR_H

#include "curtain_base.h"

class CCurtainMgr : public QObject
{
    Q_OBJECT
public:
    explicit CCurtainMgr();
    CCurtainBase * curtainInit(int );

private:
    CCurtainBase * mCurtainBase;
    
};

#endif // CURTAIN_MGR_H
