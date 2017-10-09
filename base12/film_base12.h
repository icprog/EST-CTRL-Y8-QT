#ifndef FILM_BASE12_H
#define FILM_BASE12_H

#include "./base/film_base.h"


class CFilmBase12 : public CFilmBase
{
    Q_OBJECT
public:
    explicit CFilmBase12(QWidget *parent = 0);

protected:
    void SendCmdKey(int);               //发送给下位机的命令
    virtual void filmKeyDisplay(unsigned short);      //扫描键码仅显示

public slots:
    void OnTimerFilmLong();
};

#endif // FILM_BASE12_H
