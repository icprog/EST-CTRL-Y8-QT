#ifndef FILM_CEIL8_H
#define FILM_CEIL8_H

#include "./base08/film_base8.h"


class CFilmCeil8 : public CFilmBase8
{
    Q_OBJECT
public:
    explicit CFilmCeil8(QWidget *parent = 0);
    
protected:
    static int m_filmCeil8[SYS_KEY_MAX][2];

    
};

#endif // FILM_CEIL8_H
