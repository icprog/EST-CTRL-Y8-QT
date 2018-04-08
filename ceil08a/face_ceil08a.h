#ifndef FACE_CEIL08A_H
#define FACE_CEIL08A_H

#include "./base08/face_base8.h"

#ifdef USE_CEIL_08_A

class CFaceCeil08a : public CFaceBase8
{
    Q_OBJECT
public:
    CFaceCeil08a( QWidget* parent = 0);

public slots:
    virtual void OnViewDirChange(TypeViewDir);      //显示视角切换
};

#endif  //FACE_RAIL08A_H
#endif  //FACE_CEIL08A_H
