#ifndef EXIT_RAIL08B_H
#define EXIT_RAIL08B_H

#include "./base08/exit_base8.h"


class CExitRail08b : public CExitBase8
{
    Q_OBJECT
    
public:
    explicit CExitRail08b(QWidget *parent = 0);

public slots:
    virtual void OnViewDirChange(int);      //显示视角切换
};

#endif // EXIT_RAIL08B_H
