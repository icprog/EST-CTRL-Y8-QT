#ifndef MOTION_BASE_H
#define MOTION_BASE_H

#include <QTimer>
#include <QPixmap>
#include <QRect>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "system_defines.h"


class CMotionBase : public QWidget
{
    Q_OBJECT
    
public:
    explicit CMotionBase(QWidget *parent = 0);

protected:
    virtual void myMotionInit();
    void mousePressEvent(QMouseEvent *event);

protected:
    QGraphicsScene  * sceneTube;
    QGraphicsView   * viewTube;
    QGraphicsScene  * sceneDet;
    QGraphicsView   * viewDet;

    QFrame * pixTube;
    QFrame * pixDet;
    QFrame * pixBackGround;

    QRect rectDet;
    QRect rectTube;

    int     m_iMotionDataPre[SYS_MOTION_MAX];
    int     m_iMotionDataCur[SYS_MOTION_MAX];
    bool    m_iMotionFresh[SYS_MOTION_MAX];

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

    float   m_fLiftScale;
    float   m_fLiftScalePre;
    float   m_fLiftScaleCur;

    int     m_iLiftHeight;

    QTimer * timerMotionFresh;

public slots:
    virtual void OnMotionFresh();
    virtual void OnViewDirChange(int);      //显示视角切换
};

#endif // MOTION_BASE_H
