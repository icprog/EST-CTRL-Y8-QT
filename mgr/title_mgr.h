#ifndef TITLE_MGR_H
#define TITLE_MGR_H

#include "./base/title_base.h"


class CTitleMgr : public QObject
{
    Q_OBJECT
public:
    explicit CTitleMgr();

    CTitleBase * titleInit(int);

private:

    CTitleBase * mTitleBase;
    
};

#endif // TITLE_MGR_H
