#ifndef FILM_RAIL12_H
#define FILM_RAIL12_H

#include "./base12/film_base12.h"

class CFilmRail12 : public CFilmBase12
{
    Q_OBJECT
public:
    explicit CFilmRail12(QWidget *parent = 0);
    
protected:
    void SendCmdKey(int);               //发送给下位机的命令

    static int m_filmRail10[SYS_KEY_MAX][2];

    
};

#endif // FILM_RAIL12_H
