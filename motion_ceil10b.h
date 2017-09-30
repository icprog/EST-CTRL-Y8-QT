#ifndef MOTION_CEIL10_B_H
#define MOTION_CEIL10_B_H

#include "motion_base10.h"


class CMotionCeil10b : public CMotionBase10
{
    Q_OBJECT
    
public:
    explicit CMotionCeil10b(QWidget *parent = 0);

protected:
    virtual void myMotionInit();

private:
    QGraphicsScene  * pSceneLift;

    QGraphicsView   * viewLift;

    QRect rectAccordion;
    QRect rectCeil;
    QRect rectLift;
    QRect rectStandArm;
    QRect rectTable;
    QRect rectTableDet;

    QLabel  * pixCeil;
    QFrame  * pixStandArm;
    QFrame  * pixLift;

    int m_iTableDown;

public slots:
    virtual void OnMotionFresh();
};

#endif // MOTION_CEIL10_B_H
