#ifndef MENU_MGR_H
#define MENU_MGR_H

#include "./base/menu_base.h"


class CMenuMgr : public QObject
{
    Q_OBJECT
public:
    explicit CMenuMgr();

    CMenuBase * menuInit(int);

private:
    CMenuBase * mMenuBase;
};

#endif // MENU_MGR_H
