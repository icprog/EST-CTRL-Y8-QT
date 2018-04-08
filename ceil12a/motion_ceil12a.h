#ifndef MOTION_CEIL_12A_H
#define MOTION_CEIL_12A_H

#include "./base12/motion_base12.h"

#ifdef USE_CEIL_12_A


class CMotionCeil12a : public CMotionBase12
{
    Q_OBJECT

public:
    explicit CMotionCeil12a(QWidget *parent = 0);

protected:
    virtual void myMotionInit();

private:

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
    virtual void OnViewDirChange(TypeViewDir);      //显示视角切换
};

#endif  //MOTION_CEIL_12A_H
#endif  //USE_CEIL_12_A
