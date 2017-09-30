#ifndef MOTION_UARM8_H
#define MOTION_UARM8_H

#include "motion_base8.h"

class CMotionUarm8 : public CMotionBase8
{
    Q_OBJECT
    
public:
    explicit CMotionUarm8(QWidget *parent = 0);

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    virtual void myMotionInit();

private:

    QGraphicsScene  * sceneUarm;
    QGraphicsView   * viewUarm;
    QLabel          * pixUarm;
    QRect           rectUarm;

private slots:
    virtual void OnMotionFresh();
};

#endif // MOTION_UARM8_H
