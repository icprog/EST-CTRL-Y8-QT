#ifndef MAIN_MGR_H
#define MAIN_MGR_H

#include "./base/main_base.h"


class CMainMgr : public QObject
{
    Q_OBJECT
public:
    explicit CMainMgr();

    CMainBase * mainInit(int );     //根据平台选择，创建不同的主控对象

private:
    CMainBase * mMainBase;
    
};

#endif // MAIN_MGR_H
