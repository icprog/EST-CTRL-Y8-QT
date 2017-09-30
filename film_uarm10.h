#ifndef FILM_UARM10_H
#define FILM_UARM10_H

#include "film_base10.h"

class CFilmUarm10 : public CFilmBase10
{
    Q_OBJECT
public:
    explicit CFilmUarm10(QWidget *parent = 0);
    
protected:
    void SendCmdKey(int);               //发送给下位机的命令

    static int m_filmUarm10[SYS_KEY_MAX][2];

};

#endif // FILM_UARM10_H
