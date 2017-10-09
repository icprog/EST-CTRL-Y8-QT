#include <QtGlobal>
#include<QDebug>
#include <qmath.h>

#include "./system/system_defines.h"
#include "mech_small_table.h"

CMechSmallTable::CMechSmallTable(QWidget *parent) : CMechObj(parent)
{
    setObjectName("CMechSmallTable");
}


void CMechSmallTable::BuildSurface()
{

    //构建平行与地面，穿过中心的一个面，间隔为2厘米
    //环形的点阵，角度为:
    //边上2个点的距离为: R * sin(a) / cos(a)
    //半径变化R,
    //角度变化90-270,

    //build only once
    if(arrPt.size() > 0)
        return;

    QVector3D * pV3d;

    //构建顶面
    float mCornerIndex = 15;
    for (float mIdx = 0 ; mIdx <= 360 ; mIdx += mCornerIndex)
    {
        int mX,mY;
        int mRadius = iWidth / 2;

        mX = qCos(  PI * mIdx /180 ) * mRadius ;
        mY =  qSin(  PI * mIdx /180) * mRadius;

        pV3d = new QVector3D(mX,mY,0);

        arrPt.append(pV3d);
    }

    CMechObj::BuildSurface();
}
