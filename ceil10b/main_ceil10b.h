#ifndef MAIN_CEIL10_B_H
#define MAIN_CEIL10_B_H

#include "./base10/main_base10.h"


class CMainCeil10b : public CMainBase10
{
    Q_OBJECT
    
public:
    explicit CMainCeil10b(QWidget *parent = 0);

public slots:
    virtual void OnViewChange(int);         //显示视图变更

};

#endif // MAIN_CEIL10_B_H
