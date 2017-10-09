#include<QDebug>
#include <qmath.h>

#include "./system/system_defines.h"
#include "mech_panel_brace.h"

#define PANEL_BRACE_PATCH_Z  80

CMechPanelBrace::CMechPanelBrace(QWidget *parent) : CMechObj(parent)
{
    setObjectName("CMechPanelBrace");
}

//构建立柱角上8个点
//防止与球管相撞
void CMechPanelBrace::BuildSurface()
{

    if(arrPt.size() >0)         //can only init once
        return;

    QVector3D * pt;

    //相对于中心的点的距离
    pt = new QVector3D(0 ,-iLength/2 , -iThickness + PANEL_BRACE_PATCH_Z);
    arrPt.append(pt);
    pt = new QVector3D(0 , iLength/2 , - iThickness  + PANEL_BRACE_PATCH_Z);
    arrPt.append(pt);
    pt = new QVector3D(0 ,-iLength/2, 0  + PANEL_BRACE_PATCH_Z);
    arrPt.append(pt);
    pt = new QVector3D(0 ,iLength/2, 0  + PANEL_BRACE_PATCH_Z);
    arrPt.append(pt);
    pt = new QVector3D( iWidth ,-iLength/2 ,- iThickness  + PANEL_BRACE_PATCH_Z);
    arrPt.append(pt);
    pt = new QVector3D(iWidth , iLength/2 , - iThickness + PANEL_BRACE_PATCH_Z);
    arrPt.append(pt);
    pt = new QVector3D(iWidth ,-iLength/2 ,0 + PANEL_BRACE_PATCH_Z);
    arrPt.append(pt);
    pt = new QVector3D(iWidth,iLength/2 ,0  + PANEL_BRACE_PATCH_Z);
    arrPt.append(pt);


     CMechObj::BuildSurface();
}

