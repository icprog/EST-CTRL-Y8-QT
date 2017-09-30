#ifndef TECH_MGR_H
#define TECH_MGR_H

#include "tech_base.h"


class CTechMgr : public QObject
{
    Q_OBJECT
public:
    explicit CTechMgr();

    CTechBase * techInit(int);     //根据平台选择初始化不同的发生器技术选择页面

private:

    CTechBase * mTechBase;
    
};

#endif // TECH_MGR_H
