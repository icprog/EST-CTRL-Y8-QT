#ifndef SIM_BASE_H
#define SIM_BASE_H

#include <QWidget>
#include <QTimer>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "./system/system_defines.h"
#include "button_stable.h"


class CSimBase : public QWidget
{
    Q_OBJECT
public:
    explicit CSimBase(QWidget *parent = 0);

protected:

    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);
    void mousePressEvent(QMouseEvent *event);

    virtual void OnSimulateKey(int );
    virtual void SimulateDataInit();

protected:
    QTimer * timerSimFresh;

    CButtonStable   * btnSim;
    QGraphicsView   * viewSim;
    QGraphicsScene  * sceneSim;

    short m_iPosSmart[SYS_SMART_MAX][SYS_MOTION_MAX];
    short m_iMotor[SYS_MOTION_MAX][10];

    int m_iSmartMax;
    int m_iMotionMax;

public slots:
    void OnComKeyCommand(unsigned short mKey);                //动作触发

    virtual void OnSimFresh();
    virtual void OnSimPressed();
    virtual void OnViewDirChange(int);

signals:
    void InfoMsgCtrl(int , int,void * param = 0);
};

#endif // SIM_BASE_H
