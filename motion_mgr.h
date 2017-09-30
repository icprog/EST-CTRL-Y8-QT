#ifndef MOTION_MGR_H
#define MOTION_MGR_H

#include "motion_base.h"


class CMotionMgr : public QObject
{
    Q_OBJECT
public:
    explicit CMotionMgr();

    CMotionBase * motionInit(int);

private:
    CMotionBase * mMotionBase;
    
};

#endif // MOTION_MGR_H
