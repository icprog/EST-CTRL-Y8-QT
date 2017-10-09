#include<QDebug>
#include <qmath.h>

#include "./system/system_defines.h"
#include "mech_arm.h"


CMechArm::CMechArm(QWidget *parent) : CMechObj(parent)
{
    setObjectName("CMechArm");
}

void CMechArm::BuildSurface()
{
    QVector3D * pt;

    //相对于中心的点的距离
    pt = new QVector3D(0 ,0 , 0 - iThickness / 2);
    arrPt.append(pt);
    pt = new QVector3D(0 , iLength , 0 - iThickness / 2);
    arrPt.append(pt);
    pt = new QVector3D(0 ,0, 0 + iThickness / 2);
    arrPt.append(pt);
    pt = new QVector3D(0 ,iLength, 0 + iThickness / 2);
    arrPt.append(pt);
    pt = new QVector3D( iWidth ,0 ,0 - iThickness / 2);
    arrPt.append(pt);
    pt = new QVector3D(iWidth , iLength ,0 - iThickness / 2);
    arrPt.append(pt);
    pt = new QVector3D(iWidth ,0 ,0 + iThickness / 2);
    arrPt.append(pt);
    pt = new QVector3D(iWidth,iLength ,0 + iThickness / 2);
    arrPt.append(pt);

    CMechObj::BuildSurface();
}
