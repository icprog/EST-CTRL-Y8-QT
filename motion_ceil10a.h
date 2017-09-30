#ifndef MOTION_CEIL10_A_H
#define MOTION_CEIL10_A_H

#include "motion_base10.h"


class CMotionCeil10a : public CMotionBase10
{
    Q_OBJECT
    
public:
    explicit CMotionCeil10a(QWidget *parent = 0);

protected:
    virtual void myMotionInit();

private:
    QGraphicsScene  * pSceneLift;
    QGraphicsScene  * pSceneAccordion;

    QGraphicsView   * viewLift;
    QGraphicsView   * viewAccordion;

    QRect rectAccordion;
    QRect rectCeil;
    QRect rectLift;
    QRect rectStandArm;
    QRect rectTable;
    QRect rectTableDet;

    QFrame  * pixAccordion;
    QFrame  * pixTable;
    QFrame  * pixTableDet;
    QLabel  * pixCeil;
    QFrame  * pixStandArm;
    QFrame  * pixLift;

    int m_iTableDown;

public slots:
    virtual void OnMotionFresh();
};

#endif // MOTION_CEIL10_A_H
