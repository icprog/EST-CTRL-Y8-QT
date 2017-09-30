#ifndef FACE_MGR_H
#define FACE_MGR_H

#include "face_base.h"

class CFaceMgr : public QObject
{
    Q_OBJECT
public:
    CFaceMgr();

    CFaceBase * faceInit(int );     //根据不同的平台，初始化不同的启动界面

private:
    CFaceBase * mFaceBase;
    

};

#endif // FACE_MGR_H
