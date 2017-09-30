#ifndef FAST_MGR_H
#define FAST_MGR_H

#include "fast_base.h"


class CFastMgr : public QObject
{
    Q_OBJECT

public:
    explicit CFastMgr();

    CFastBase * fastInit(int );     //根据平台选择，初始化不同的快捷对象

private:
    CFastBase * mFastBase;
    
};

#endif // FAST_MGR_H
