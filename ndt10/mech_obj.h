#ifndef CMECHOBJ_H
#define CMECHOBJ_H

#include <QWidget>
#include <QVector3D>

#define MECH_INIT_MCEN  1               /*centor init*/
#define MECH_INIT_DIMENSION  2      /*dimension init*/


class CMechObj : public QWidget
{
    Q_OBJECT
public:
    explicit CMechObj(QWidget *parent = 0);

    QList<QVector3D * > arrPt;     //边或表面上的点，相对位置，相对于中心点
    QList<QVector3D * > arrPtRotate;     //旋转后的相对点，旋转是绝对量旋转，

    QVector3D   mechCentor;        //centor of object,中心点，绝对位置

    virtual int getX();
    virtual int getXMin();
    virtual int getXMax();

    virtual int getZ();
    virtual int getZMin();
    virtual int getZMax();

    virtual int getY();
    virtual int getYMin();
    virtual int getYMax();

    virtual int getDistanceMin(CMechObj *);
private:

    void BuildCornerPoints();

protected:
    bool enablePointWrite;
    //centor
    //origin point is x Long table Min data //y Tube min data //z floor

    //QVector3D   rotateCentor;       //centor for rotate

    int iInitState;         //init state of current object.

    float mAngle;         //当前角度，用于平板旋转

    //width,height,thickness
    int iThickness;     //thick of object,refer to Z
    int iWidth;          //width of object,refer to X,Long table run direction
    int iLength;        //length of object,refer to Y,Flat panel run direction.

    int iCanRorate; //object can rotate or not.

public:
    virtual void setMechCentor(int,int,int);     //set mechCentor
    //void setRotateCentor(QVector3D &);   //set rotateCentor
    virtual void setDimension(int,int,int);             //set iWidth,iLength,iThickness
    //void setRotateFcn(int);                          //object can rotate or not.

    virtual void BuildSurface();
    virtual void SaveMechPointsReal();           //保存实际点坐标位置

    void SaveMechPointsRef();           //保存参考点坐标位置


    void MoveX(int);
    void MoveY(int);
    void MoveZ(int);
    void MoveXYZ(int,int,int);
signals:

public slots:
};

#endif // CMECHOBJ_H
