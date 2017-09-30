#ifndef MOTION_UARM10_H
#define MOTION_UARM10_H

#include "motion_base10.h"


class CMotionUarm10 : public CMotionBase10
{
    Q_OBJECT
    
public:
    explicit CMotionUarm10(QWidget *parent = 0);

protected:
    virtual void myMotionInit();

private:

    QGraphicsScene  * sceneUarm;

    QGraphicsView   * viewUarm;

    QLabel * pixUarm;

    QRect rectUarm;

private slots:
    virtual void OnMotionFresh();

};

#endif // MOTION_UARM10_H
