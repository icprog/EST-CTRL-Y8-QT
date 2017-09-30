#ifndef MOTION_RAIL12_H
#define MOTION_RAIL12_H

#include "motion_base12.h"


class CMotionRail12 : public CMotionBase12
{
    Q_OBJECT

public:
    explicit CMotionRail12(QWidget *parent = 0);

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

#endif // MOTION_RAIL12_H
