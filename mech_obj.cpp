#include "mech_obj.h"
#include "qmath.h"

#include <QCoreApplication>
#include <QSettings>

CMechObj::CMechObj(QWidget *parent) : QWidget(parent)
{
    mechCentor    =   QVector3D(0,0,0);
    //rotateCentor   =   QVector3D(0,0,0);

    iThickness       = 0;
    iWidth             = 0;
    iLength            = 0;

    iInitState = 0;
    iCanRorate = false;

    enablePointWrite = false;
}

void CMechObj::setMechCentor(int x,int y,int z)
{
    mechCentor.setX(x);
    mechCentor.setY(y);
    mechCentor.setZ(z);

    iInitState |= MECH_INIT_MCEN;
}
/*
void CMechObj::setRotateCentor(QVector3D & rCen)
{
    rotateCentor = rCen;
}*/

void CMechObj::setDimension(int wid,int len,int thick)
{
    iThickness = thick;
    iWidth = wid;
    iLength = len;

    iInitState |= MECH_INIT_DIMENSION;
}
/*
void CMechObj::setRotateFcn(int bRot)
{
    iCanRorate = bRot;
}
*/
void CMechObj::MoveX(int mPos)
{
    mechCentor.setX(mPos);
}
void CMechObj::MoveY(int mPos)
{
    mechCentor.setY(mPos);
}
void CMechObj::MoveZ(int mPos)
{
    mechCentor.setZ(mPos);
}
void CMechObj::MoveXYZ(int mXPos,int mYPos,int mZPos)
{
    mechCentor.setX(mXPos);
    mechCentor.setY(mYPos);
    mechCentor.setZ(mZPos);
}
void CMechObj::BuildSurface()
{
    SaveMechPointsRef();
}
int CMechObj::getX()
{

    return mechCentor.x();
}
int CMechObj::getXMin()
{
    QList<QVector3D * >  Ptr;

    if(arrPtRotate.size() > 0)
        Ptr = arrPtRotate;
    else
        Ptr = arrPt;

    int minTemp = 1000000;
    for(int mIdx = 0 ; mIdx < Ptr.size() ; mIdx++)
    {
        if(Ptr.at(mIdx)->x() < minTemp)
            minTemp = Ptr.at(mIdx)->x();
    }

    return minTemp + mechCentor.x();
}
int CMechObj::getXMax()
{
    QList<QVector3D * >  Ptr;

    if(arrPtRotate.size() > 0)
        Ptr = arrPtRotate;
    else
        Ptr = arrPt;

    int maxTemp = -1000000;
    for(int mIdx = 0 ; mIdx < Ptr.size() ; mIdx++)
    {
        if(Ptr.at(mIdx)->x() > maxTemp)
            maxTemp = Ptr.at(mIdx)->x();
    }

    return maxTemp + mechCentor.x();
}
int CMechObj::getY()
{

    return mechCentor.y();
}
int CMechObj::getYMin()
{
    QList<QVector3D * >  Ptr;

    if(arrPtRotate.size() > 0)
        Ptr = arrPtRotate;
    else
        Ptr = arrPt;

    int minTemp = 1000000;
    for(int mIdx = 0 ; mIdx < Ptr.size() ; mIdx++)
    {
        if(Ptr.at(mIdx)->y() < minTemp)
            minTemp = Ptr.at(mIdx)->y();
    }

    return minTemp + mechCentor.y();
}
int CMechObj::getYMax()
{
    QList<QVector3D * >  Ptr;

    if(arrPtRotate.size() > 0)
        Ptr = arrPtRotate;
    else
        Ptr = arrPt;

    int maxTemp = -1000000;
    for(int mIdx = 0 ; mIdx < Ptr.size() ; mIdx++)
    {
        if(Ptr.at(mIdx)->y() > maxTemp)
            maxTemp = Ptr.at(mIdx)->y();
    }

    return maxTemp + mechCentor.y();
}

int CMechObj::getZ()
{
    return mechCentor.z();
}


int CMechObj::getZMin()
{
    QList<QVector3D * >  Ptr;

    if(arrPtRotate.size() > 0)
        Ptr = arrPtRotate;
    else
        Ptr = arrPt;

    int minTemp = 1000000;
    for(int mIdx = 0 ; mIdx < Ptr.size() ; mIdx++)
    {
        if(Ptr.at(mIdx)->z() < minTemp)
            minTemp = Ptr.at(mIdx)->z();
    }

    return minTemp + mechCentor.z();
}
int CMechObj::getZMax()
{
    QList<QVector3D * >  Ptr;

    if(arrPtRotate.size() > 0)
        Ptr = arrPtRotate;
    else
        Ptr = arrPt;

    int maxTemp = -1000000;
    for(int mIdx = 0 ; mIdx < Ptr.size() ; mIdx++)
    {
        if(Ptr.at(mIdx)->z() > maxTemp)
            maxTemp = Ptr.at(mIdx)->z();
    }

    return maxTemp + mechCentor.z();
}


int CMechObj::getDistanceMin(CMechObj * obj)
{

    int mDistanceMin = 10000;   //最小值
    int mDistance;   //临时数据


    float distX,distY,distZ;

    for(int mIdx = 0 ; mIdx < arrPt.size() ; mIdx++)
    {
        for(int mCtr = 0 ; mCtr < obj->arrPt.size() ; mCtr++)
        {
            distX = qPow(arrPt.at(mIdx)->x() + mechCentor.x() - obj->arrPt.at(mCtr)->x() - obj->mechCentor.x(),2);
            distY = qPow(arrPt.at(mIdx)->y() + mechCentor.y() - obj->arrPt.at(mCtr)->y() - obj->mechCentor.y(),2);
            distZ = qPow(arrPt.at(mIdx)->z() + mechCentor.z() - obj->arrPt.at(mCtr)->z() - obj->mechCentor.z(),2);

            mDistance = qSqrt( distX + distY + distZ);

            if(mDistance < mDistanceMin)
            {
                mDistanceMin = mDistance;
            }
        }
    }

    return mDistanceMin;
}


void CMechObj::SaveMechPointsRef()
{
    if(!enablePointWrite)
        return;

    if(arrPt.size() == 0)
        return;

    QVector3D * vectXmin,*vectXmax;
    QVector3D * vectYmin,*vectYmax;
    QVector3D * vectZmin,*vectZmax;

    int minX = 1000000,maxX = -1000000;
    int minY = 1000000,maxY = -1000000;
    int minZ = 1000000,maxZ = -1000000;

    vectXmin =  arrPt.at(0);
    vectXmax =  arrPt.at(0);
    vectYmin =  arrPt.at(0);
    vectYmax =  arrPt.at(0);
    vectZmin =  arrPt.at(0);
    vectZmax =  arrPt.at(0);

    for(int mIdx = 0 ; mIdx < arrPt.size() ; mIdx++)
    {
        //保存X方向最小的点坐标
        if(arrPt.at(mIdx)->x() < minX)
        {
            minX = arrPt.at(mIdx)->x();
            vectXmin = arrPt.at(mIdx);
        }

        //保存X方向最大的点坐标
        if(arrPt.at(mIdx)->x() > maxX)
        {
            maxX = arrPt.at(mIdx)->x();
            vectXmax  = arrPt.at(mIdx);
        }

        //保存Y方向最小的点坐标
        if(arrPt.at(mIdx)->y() < minY)
        {
            minY = arrPt.at(mIdx)->y();
            vectYmin = arrPt.at(mIdx);
        }
        //    保存Y方向最大的点坐标
        if(arrPt.at(mIdx)->y() > maxY)
        {
            maxY = arrPt.at(mIdx)->y();
            vectYmax  = arrPt.at(mIdx);
        }
        //    保存Z方向最小的点坐标
        if(arrPt.at(mIdx)->z() < minZ)
        {
            minZ = arrPt.at(mIdx)->z();
            vectZmin = arrPt.at(mIdx);
        }
        //    保存Z方向最大的点坐标
        if(arrPt.at(mIdx)->z() > maxZ)
        {
            maxZ = arrPt.at(mIdx)->z();
            vectZmax  = arrPt.at(mIdx);
        }
    }

    QSettings * pPtSave = new QSettings(QCoreApplication::applicationDirPath() + "/SurfacePoints.ini",QSettings::IniFormat);

    //    保存点的个数
    pPtSave->setValue(objectName() + "/PtNum",arrPt.size());

    //临时变量
    QString strKey;

    strKey.sprintf("x=%f::y=%f::z=%f",vectXmin->x(),vectXmin->y(),vectXmin->z());
    pPtSave->setValue(objectName() + "/Xmin",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectXmax->x(),vectXmax->y(),vectXmax->z());
    pPtSave->setValue(objectName() + "/Xmax",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectYmin->x(),vectYmin->y(),vectYmin->z());
    pPtSave->setValue(objectName() + "/Ymin",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectYmax->x(),vectYmax->y(),vectYmax->z());
    pPtSave->setValue(objectName() + "/Ymax",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectZmin->x(),vectZmin->y(),vectZmin->z());
    pPtSave->setValue(objectName() + "/Zmin",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectZmax->x(),vectZmax->y(),vectZmax->z());
    pPtSave->setValue(objectName() + "/Zmax",strKey);
}

void CMechObj::SaveMechPointsReal()
{
    if(!enablePointWrite)
        return;

    if(arrPt.size() == 0)
        return;

    QVector3D * vectXmin,*vectXmax;
    QVector3D * vectYmin,*vectYmax;
    QVector3D * vectZmin,*vectZmax;

    int minX = 1000000,maxX = -1000000;
    int minY = 1000000,maxY = -1000000;
    int minZ = 1000000,maxZ = -1000000;

    vectXmin =  arrPt.at(0);
    vectXmax =  arrPt.at(0);
    vectYmin =  arrPt.at(0);
    vectYmax =  arrPt.at(0);
    vectZmin =  arrPt.at(0);
    vectZmax =  arrPt.at(0);

    QList<QVector3D * >  Ptr;

    if(arrPtRotate.size() > 0)
        Ptr = arrPtRotate;
    else
        Ptr = arrPt;

    for(int mIdx = 0 ; mIdx < Ptr.size() ; mIdx++)
    {
        //保存X方向最小的点坐标
        if(Ptr.at(mIdx)->x() < minX)
        {
            minX = Ptr.at(mIdx)->x();
            vectXmin = Ptr.at(mIdx);
        }

        //保存X方向最大的点坐标
        if(Ptr.at(mIdx)->x() > maxX)
        {
            maxX = Ptr.at(mIdx)->x();
            vectXmax  = Ptr.at(mIdx);
        }

        //保存Y方向最小的点坐标
        if(Ptr.at(mIdx)->y() < minY)
        {
            minY = Ptr.at(mIdx)->y();
            vectYmin = Ptr.at(mIdx);
        }
        //    保存Y方向最大的点坐标
        if(Ptr.at(mIdx)->y() > maxY)
        {
            maxY = Ptr.at(mIdx)->y();
            vectYmax  = Ptr.at(mIdx);
        }
        //    保存Z方向最小的点坐标
        if(Ptr.at(mIdx)->z() < minZ)
        {
            minZ = Ptr.at(mIdx)->z();
            vectZmin = Ptr.at(mIdx);
        }
        //    保存Z方向最大的点坐标
        if(Ptr.at(mIdx)->z() > maxZ)
        {
            maxZ = Ptr.at(mIdx)->z();
            vectZmax  = Ptr.at(mIdx);
        }
    }

    QSettings * pPtSave = new QSettings(QCoreApplication::applicationDirPath() + "/SurfacePoints.ini",QSettings::IniFormat);

    //    保存点的个数
    pPtSave->setValue(objectName() + "/PtNum",Ptr.size());

    //临时变量
    QString strKey;

    strKey.sprintf("x=%f::y=%f::z=%f", mechCentor.x(),mechCentor.y(),mechCentor.z());
    pPtSave->setValue(objectName() + "/XYZ",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectXmin->x() + mechCentor.x(),vectXmin->y()+mechCentor.y(),vectXmin->z()+mechCentor.z());
    pPtSave->setValue(objectName() + "/Xrmin",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectXmax->x() + mechCentor.x(),vectXmax->y()+mechCentor.y(),vectXmax->z()+mechCentor.z());
    pPtSave->setValue(objectName() + "/Xrmax",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectYmin->x() + mechCentor.x(),vectYmin->y()+mechCentor.y(),vectYmin->z()+mechCentor.z());
    pPtSave->setValue(objectName() + "/Yrmin",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectYmax->x() + mechCentor.x(),vectYmax->y()+mechCentor.y(),vectYmax->z()+mechCentor.z());
    pPtSave->setValue(objectName() + "/Yrmax",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectZmin->x() + mechCentor.x(),vectZmin->y()+mechCentor.y(),vectZmin->z()+mechCentor.z());
    pPtSave->setValue(objectName() + "/Zrmin",strKey);

    strKey.sprintf("x=%f::y=%f::z=%f",vectZmax->x() + mechCentor.x(),vectZmax->y()+mechCentor.y(),vectZmax->z()+mechCentor.z());
    pPtSave->setValue(objectName() + "/Zrmax",strKey);
}

