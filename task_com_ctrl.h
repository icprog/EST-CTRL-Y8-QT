#ifndef     TASK_COM_CTRL_H
#define     TASK_COM_CTRL_H

#include "task_com_base.h"


class CTaskComCtrl :public CTaskComBase
{
    Q_OBJECT
public:
    CTaskComCtrl();

public:

    void CreateTask(unsigned short wType,unsigned short* buf,unsigned short wcount);

private:
    void firmWareVersion(unsigned short * , char *);      //convert control baord firm ware version from hex to char

protected:

    virtual void SendTaskComm();

    virtual void ReceiveTaskComm();
    virtual void ProcessRxData();

};


#endif  //TASK_COM_CTRL_H



