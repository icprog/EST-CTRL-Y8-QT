#ifndef MOTION_CEIL8_H
#define MOTION_CEIL8_H

#include "./base08/motion_base8.h"


class CMotionCeil8 : public CMotionBase8
{
    Q_OBJECT
    
public:
    explicit CMotionCeil8(QWidget *parent = 0);
    
protected:
    virtual void myMotionInit();

private:

    QGraphicsScene  * sceneLift;
    QGraphicsView   * viewLift;

    QFrame * pixLift;
    QLabel * pixStandArm;
    QLabel * pixCeil;

    QRect rectLift;
    QRect rectStandArm;
    QRect rectCeil;

private slots:
    virtual void OnMotionFresh();
};

#endif // MOTION_CEIL8_H
