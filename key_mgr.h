#ifndef KEY_MGR_H
#define KEY_MGR_H

#include "key_base.h"


class CKeyMgr : public QObject
{
    Q_OBJECT
public:
    explicit CKeyMgr();

    CKeyBase * keyInit(int);        //根据不同平台，初始化液晶按键

private:
    CKeyBase * mTestBase;
    
};

#endif // KEY_MGR_H
