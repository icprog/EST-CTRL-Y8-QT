#include<QDebug>
#include <qmath.h>

#include "system_defines.h"
#include "mech_tube.h"

#define TUBE_BOTTOM_STEP  50
#define TUBE_Y_FOCUS_2_BORDER    220        /*球管Y方向上中心点距离小端170*/
#define TUBE_Z_FOCUS_2_BOTTON    300       /*球管Z方向上中心点距离限束器底面的距离*/
CMechTube::CMechTube(QWidget *parent) : CMechObj(parent)
{
    setObjectName("CMechTube");
}

//针对球管部件，
//只维护底部一个面，
//球管Y方向800
//球管Y方向上中心点距离小端170
//球管X方向600
//球管X方向上中心点在中心
void CMechTube::BuildSurface()
{

    //build only once
    if(arrPt.size() > 0)
        return;

    QVector3D * pV3d;
    //Y方向
    for(int mIdxY = 0; mIdxY  <= iLength ; mIdxY += TUBE_BOTTOM_STEP)
    {
        //X方向
        for(int mIdxX = iWidth / 2; mIdxX  >= -iWidth / 2 ; mIdxX -= TUBE_BOTTOM_STEP)
        {

            pV3d = new QVector3D(mIdxX , mIdxY - TUBE_Y_FOCUS_2_BORDER, 0 - TUBE_Z_FOCUS_2_BOTTON);

            arrPt.append(pV3d);
        }
    }

    CMechObj::BuildSurface();
}
