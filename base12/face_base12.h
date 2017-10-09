#ifndef FACE_BASE12_H
#define FACE_BASE12_H

#include "./base/face_base.h"

class CFaceBase12 : public CFaceBase
{
    Q_OBJECT
public:
    CFaceBase12( QWidget* parent = 0);

public slots:
    virtual void OnViewDirChange(int);      //显示视角切换
};

#endif // FACE_BASE12_H
