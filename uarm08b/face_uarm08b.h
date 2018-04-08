#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_B

#ifndef FACE_RAIL08B_H
#define FACE_RAIL08B_H

#include "./base08/face_base8.h"

class CFaceRail08b : public CFaceBase8
{
    Q_OBJECT
public:
    CFaceRail08b( QWidget* parent = 0);

public slots:
    virtual void OnViewDirChange(int);      //显示视角切换
};

#endif // FACE_RAIL08B_H
#endif //USE_RAIL_08_B
