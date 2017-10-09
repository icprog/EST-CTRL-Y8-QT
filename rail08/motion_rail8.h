#ifndef MOTION_RAIL8_H
#define MOTION_RAIL8_H

#include "./base08/motion_base8.h"


class CMotionRail8 : public CMotionBase8
{
    Q_OBJECT
    
public:
    explicit CMotionRail8(QWidget *parent = 0);

protected:
    virtual void myMotionInit();

private:

    QGraphicsView   * viewAccordion;
    QGraphicsScene  * pSceneAccordion;

    QLabel * pixStand;
    QLabel * pixTable;
    QFrame * pixAccordion;
    QFrame * pixBucky;

    QRect rectStand;
    QRect rectAccordion;
    QRect rectTable;
    QRect rectTableDet;

    int m_iTableDown;

private slots:
    virtual void OnMotionFresh();
};

#endif // MOTION_RAIL8_H
