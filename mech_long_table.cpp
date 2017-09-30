#include<QDebug>
#include <qmath.h>

#include "system_defines.h"
#include "mech_long_table.h"

//长台表面对象
//X、Y方向上的间隔距离
#define LONG_TABLE_STEP_X  100
#define LONG_TABLE_STEP_Y  50

CMechLongTable::CMechLongTable(QWidget *parent) : CMechObj(parent)
{
    //对象名称
    setObjectName("CMechLongTable");

    setGeometry(0,0,300,500);
}

//构建长台表面，用于碰撞检测
//    长台表面上的点。
//    用于检测横臂降时是否会碰到
//    用于检测球管升降时是否会碰到
//    用于检测球管转动时是否相撞
//    他的最小值非0，参考长台最左边到直线导轨顶端的距离
//    长2100，X方向，参考床面长度
//    宽850，Y方向，参考床面宽度
//    高800，Z防线，参考床面到地面高度
//    该面包含4条边和面上的点，
//    间隔距离为X方向100mm，Y方向100mm

//X方向表面数值参考长台最左端
//Y方向表面数值参考长台最前端
//Z方向表面数值参考地面
void CMechLongTable::BuildSurface()
{
    //build only once
    if(arrPt.size() > 0)
        return;

    QVector3D * pV3d;

    //Y方向，数值固定
    for(int mIdxY = iLength ; mIdxY  >= 0 ; mIdxY -= LONG_TABLE_STEP_Y)
    {
        //X方向
        for(int mIdxX = 0 ; mIdxX  >= 0 - iWidth; mIdxX -= LONG_TABLE_STEP_X)
        {

            //创建表面的参考点,Z点默认为0，Z平面
            pV3d = new QVector3D(mIdxX,mIdxY,0 );

            //添加到队列
            arrPt.append(pV3d);
        }
    }
    /*
    for(int mIdxY = iLength ; mIdxY  >= 0 ; mIdxY -= LONG_TABLE_STEP_Y)
    {
        for(int mIdxX = iWidth ; mIdxX  >= 0 ; mIdxX -= LONG_TABLE_STEP_X)
        {

            //创建表面的参考点
            pV3d = new QVector3D(mIdxX,mIdxY,mechCentor.z() );

            //添加到队列
            arrPt.append(pV3d);
        }
    }
    */
    //基类功能
    CMechObj::BuildSurface();
}



