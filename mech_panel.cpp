#include<QDebug>
#include <qmath.h>

#include "system_defines.h"
#include "mech_panel.h"

//#define MECH_PANEL_X_OFFSET 0
//#define MECH_PANEL_Z_OFFSET 0
//#define MECH_PANEL_X_OFFSET  90
//#define MECH_PANEL_Z_OFFSET 110

//#define MECH_PANEL_STEP  280
//#define MECH_PANEL_STEP  140
#define MECH_PANEL_STEP  20
#define MECH_PANEL_X_OFFSET  0
//#define MECH_PANEL_Z_OFFSET 110
#define MECH_PANEL_Z_OFFSET 100

CMechPanel::CMechPanel(QWidget *parent) : CMechObj(parent)
{
    setObjectName("CMechPanel");
}

//平板水平代表0
//以0度方式构建初始表面
//前提知道平板中心点，平板三维
//表面上所有的点，是相对于中心点的相对位置
//中心点可以移动，
//三维实际点根据中心点和表面点计算得出
//平板支持旋转，围绕Y轴转动。
//平板转动后，表面相对的点位置变更。
//Y方向0点为平板Y方向中心
//X方向0点为平板Y方向转轴在X方向的投影
//Z方向0点
void CMechPanel::BuildSurface()
{

    if(arrPt.size() >0)         //can only init once
        return;

    QVector3D * pV3d;

    /*
    //X方向
    for (int mIdx = (0 - iWidth/2) ; mIdx <=  (0 + iWidth/2) ; mIdx += MECH_PANEL_STEP)
    {
        //Y方向
        for (int mCtr = (0 - iLength/2) ; mCtr <=  (0 + iLength/2) ; mCtr += MECH_PANEL_STEP)
        {

            pV3d = new QVector3D(mIdx + MECH_PANEL_X_OFFSET,mCtr,MECH_PANEL_Z_OFFSET);
            arrPt.append(pV3d);

            pV3d = new QVector3D(mIdx + MECH_PANEL_X_OFFSET,mCtr,MECH_PANEL_Z_OFFSET);
            arrPtRotate.append(pV3d);
        }
    }
    */
    //X方向
    for (int mIdx = (0 - iWidth/2) ; mIdx <=  (0 + iWidth/2) ; mIdx += MECH_PANEL_STEP)
    {
        //Y方向
        for (int mCtr = (0 - iLength/2) ; mCtr <=  (0 + iLength/2) ; mCtr += MECH_PANEL_STEP)
        {

            pV3d = new QVector3D(mIdx + MECH_PANEL_X_OFFSET,mCtr,MECH_PANEL_Z_OFFSET);
            arrPt.append(pV3d);

            pV3d = new QVector3D(mIdx + MECH_PANEL_X_OFFSET,mCtr,MECH_PANEL_Z_OFFSET + iThickness);
            arrPt.append(pV3d);

            pV3d = new QVector3D(mIdx + MECH_PANEL_X_OFFSET,mCtr,MECH_PANEL_Z_OFFSET);
            arrPtRotate.append(pV3d);

            pV3d = new QVector3D(mIdx + MECH_PANEL_X_OFFSET,mCtr,MECH_PANEL_Z_OFFSET + iThickness);
            arrPtRotate.append(pV3d);
        }
    }

    CMechObj::BuildSurface();
}
///
/// \brief CMechPanel::setAngle
/// \param ang 当前平板角度，绝对值
///根据当前角度，计算每个表面上的点的相对位置
void CMechPanel::setAngle(float ang)
{

    mAngle = ang * PI /180;

    if(arrPt.size() == 0)
        return;

    QVector3D vec11(qCos(mAngle),0,qSin(mAngle));
    QVector3D vec21(0,1,0);
    QVector3D vec31(-qSin(mAngle),0,qCos(mAngle));

    for(int mIdx = 0 ; mIdx < arrPt.size() ; mIdx ++)
    {
        float mX,mY,mZ;

        mX = QVector3D::dotProduct(*arrPt.at(mIdx),vec11);
        mY = QVector3D::dotProduct(*arrPt.at(mIdx),vec21);
        mZ = QVector3D::dotProduct(*arrPt.at(mIdx),vec31);

        arrPtRotate[mIdx]->setX(mX);
        arrPtRotate[mIdx]->setY(mY);
        arrPtRotate[mIdx]->setZ(mZ);
    }
}

int CMechPanel::getDistanceMin(CMechObj * obj)
{

    int mDistanceMin = 10000;   //最小值
    int mDistance;   //临时数据

    float distX,distY,distZ;

    for(int mIdx = 0 ; mIdx < arrPtRotate.size() ; mIdx++)
    {
        for(int mCtr = 0 ; mCtr < obj->arrPt.size() ; mCtr++)
        {
            distX = qPow(arrPtRotate.at(mIdx)->x() + mechCentor.x() - obj->arrPt.at(mCtr)->x() - obj->mechCentor.x(),2);
            distY = qPow(arrPtRotate.at(mIdx)->y() + mechCentor.y() - obj->arrPt.at(mCtr)->y() - obj->mechCentor.y(),2);
            distZ = qPow(arrPtRotate.at(mIdx)->z() + mechCentor.z() - obj->arrPt.at(mCtr)->z() - obj->mechCentor.z(),2);

            mDistance = qSqrt( distX + distY + distZ);

            if(mDistance < mDistanceMin)
            {
                mDistanceMin = mDistance;

               // PosA = mIdx;
             //   PosB = mCtr;
            }
        }
    }

    /*
    qDebug()<<  "PosA="<<PosA;
    qDebug()<<  "PosB="<<PosB;

    qDebug()<< arrPtRotate.at(PosA)->x() + mechCentor.x() <<  "XXX"<<obj->arrPt.at(PosB)->x() + obj->mechCentor.x();
    qDebug()<< arrPtRotate.at(PosA)->y() + mechCentor.y() <<  "YYY"<<obj->arrPt.at(PosB)->y() + obj->mechCentor.y();
    qDebug()<< arrPtRotate.at(PosA)->z() + mechCentor.z() <<  "ZZZ"<<obj->arrPt.at(PosB)->z() + obj->mechCentor.z();
    */
    return mDistanceMin;
}






