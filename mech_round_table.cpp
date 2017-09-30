#include <QtGlobal>
#include<QDebug>
#include <qmath.h>

#include "system_defines.h"
#include "mech_round_table.h"

#define ROUND_RADIUS_STEP 70    /*数字太小，数据太多；数字太大，两个圈之间存在检测空隙*/
#define ROUND_RADIUS_MIN    150

CMechRoundTable::CMechRoundTable(QWidget *parent) : CMechObj(parent)
{
    setObjectName("CMechRoundTable");

}

//构建平行与地面，穿过中心的一个面，间隔为2厘米
//环形的点阵，角度为:
//边上2个点的距离为: R * sin(a) / cos(a)
//半径变化R,
//角度变化90-270,
void CMechRoundTable::BuildSurface()
{

    //build only once
    if(arrPt.size() > 0)
        return;

    QVector3D * pV3d;

    //构建顶面
    float mCornerIndex = 1.9;
    for(int mRad = iWidth / 2; mRad >= ROUND_RADIUS_MIN ; mRad -= ROUND_RADIUS_STEP)
    {
        for (float mIdx = 90 ; mIdx <= 270 ; mIdx += mCornerIndex)
        {
            int mX,mY;
            int mRadius = iWidth / 2;

            mX = qCos(  PI * mIdx /180 ) * mRadius ;
            mY =  qSin(  PI * mIdx /180) * mRadius;

            pV3d = new QVector3D(mX,mY,0);

            arrPt.append(pV3d);
        }

        mCornerIndex += 2;
    }

    CMechObj::BuildSurface();
}
