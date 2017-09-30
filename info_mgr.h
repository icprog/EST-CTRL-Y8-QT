#ifndef INFO_MGR_H
#define INFO_MGR_H

#include "info_base.h"


class CInfoMgr : public QObject
{
    Q_OBJECT
public:
    explicit CInfoMgr();

    CInfoBase * infoInit(int);              //根据平台选择，初始化不同的信息显示对象

private:
    CInfoBase * mInfoBase;
};

#endif // INFO_MGR_H
