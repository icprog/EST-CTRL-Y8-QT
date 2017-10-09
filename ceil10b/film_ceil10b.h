#ifndef FILM_CEIL10B_H
#define FILM_CEIL10B_H

#include "./base10/film_base10.h"


class CFilmCeil10b : public CFilmBase10
{
    Q_OBJECT

public:
    explicit CFilmCeil10b(QWidget *parent = 0);

protected:
    void SendCmdKey(int);               //发送给下位机的命令

    static int m_filmCeil10b[SYS_KEY_MAX][2];

};

#endif // FILM_CEIL10B_H
