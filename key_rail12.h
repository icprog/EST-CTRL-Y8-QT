#ifndef KEY_RAIL12_H
#define KEY_RAIL12_H

#include "key_base12.h"


class CKeyRail12 : public CKeyBase12
{
    Q_OBJECT

public:
    explicit CKeyRail12(QWidget *parent = 0);

protected:

    void keyCodeInit();

public slots:
    virtual void OnViewDirChange(int viewerDir);    //角度视图切换槽
};

#endif // KEY_RAIL12_H
