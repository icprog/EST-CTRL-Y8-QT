#ifndef MOTOR_MGR_H
#define MOTOR_MGR_H

#include "motor_base.h"
#include "motor_ndt.h"      /*无损探伤位置校正*/


class CMotorMgr : public QObject
{
    Q_OBJECT
public:
    explicit CMotorMgr();

    void motorInit(int );
    
    int motorCheck();       //校验电机的校正数据

    CMotorBase * g_motorConfig[SYSTEM_MOTOR_MAX];
    CMotorNdt   * g_motorNdt;

    int getLimitMin(int);
    int getLimitMax(int);

private:
    int m_iPlatform;
};

#endif // MOTOR_MGR_H
