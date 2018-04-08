#ifndef EXIT_BASE12_H
#define EXIT_BASE12_H

#include "./base/exit_base.h"


class CExitBase12 : public CExitBase
{
    Q_OBJECT
    
public:
    explicit CExitBase12(QWidget *parent = 0);

public slots:
    virtual void OnViewDirChange(int);      //显示视角切换
};

#endif // EXIT_BASE12_H
