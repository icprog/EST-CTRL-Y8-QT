#ifndef FILM_CEIL10A_H
#define FILM_CEIL10A_H

#include "film_base10.h"

class CFilmCeil10a : public CFilmBase10
{
    Q_OBJECT
public:
    explicit CFilmCeil10a(QWidget *parent = 0);
    
protected:
    void SendCmdKey(int);               //发送给下位机的命令

    static int m_filmCeil10a[SYS_KEY_MAX][2];

};

#endif // FILM_CEIL10A_H
