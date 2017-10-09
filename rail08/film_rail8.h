#ifndef FILM_RAIL8_H
#define FILM_RAIL8_H

#include "./base08/film_base8.h"

class CFilmRail8 : public CFilmBase8
{
    Q_OBJECT
public:
    explicit CFilmRail8(QWidget *parent = 0);

private:
    void SendCmdKey00(int);               //老协议版本，发送一键立位，一键卧位，斜线键码
    void SendCmdKey01(int);               //新协议，发送立位1.8米，立位1.1米，卧位

protected:

    static int m_filmRail8[SYS_KEY_MAX][2];

    void SendCmdKey(int);               //发送给下位机的命令

    
};

#endif // FILM_RAIL8_H
