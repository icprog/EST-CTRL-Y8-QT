#include<QDebug>
#include <qmath.h>

#include "./system/system_defines.h"
#include "mech_stand.h"

#define BORDER_STEP_MM  10

CMechStand::CMechStand(QWidget *parent) : CMechObj(parent)
{
    setObjectName("CMechStand");
}

//构建立柱角上8个点
//防止与球管相撞
void CMechStand::BuildSurface()
{

    if(arrPt.size() >0)         //can only init once
        return;

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

