#ifndef     TASK_COM_KEY_H
#define     TASK_COM_KEY_H

#include "task_com_base.h"


class CTaskComKey :public CTaskComBase
{
    Q_OBJECT
public:
    CTaskComKey();

protected:

    virtual void SendTaskComm();

    virtual void ReceiveTaskComm();
    virtual void ProcessRxData();

};


#endif  //TASK_COM_KEY_H



