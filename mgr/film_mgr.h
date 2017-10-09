#ifndef FILM_MGR_H
#define FILM_MGR_H

#include "./base/film_base.h"


class CFilmMgr : public QObject
{
    Q_OBJECT
public:
    explicit CFilmMgr();

    CFilmBase * filmInit(int);       //根据平台选择，初始化不同的Key
    
private:
    CFilmBase * mKeyBase;
};

#endif // FILM_MGR_H
