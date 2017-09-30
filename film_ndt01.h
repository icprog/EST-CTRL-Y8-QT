#ifndef FILM_NDT01_H
#define FILM_NDT01_H

#include "film_base10.h"

class CFilmNdt01 : public CFilmBase10
{
    Q_OBJECT
public:
    explicit CFilmNdt01(QWidget *parent = 0);
    
    virtual void filmLed(int led = 0);                 //控制物理按键灯显示，控制任务
protected:
    void SendCmdKey(int);               //发送给下位机的命令

    static int m_filmNdt[SYS_KEY_MAX][2];

    
};

#endif // FILM_NDT01_H
