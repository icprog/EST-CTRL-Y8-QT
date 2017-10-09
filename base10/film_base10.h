#ifndef FILM_BASE10_H
#define FILM_BASE10_H

#include "./base/film_base.h"


class CFilmBase10 : public CFilmBase
{
    Q_OBJECT
public:
    explicit CFilmBase10(QWidget *parent = 0);

protected:
    void SendCmdKey(int);               //发送给下位机的命令

public slots:
    void OnTimerFilmLong();
    
};

#endif // FILM_BASE10_H
