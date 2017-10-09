#ifndef STATUS_RAIL12_H
#define STATUS_RAIL12_H

#include "./base12/status_base12.h"


class CStatusRail12 : public CStatusBase12
{
    Q_OBJECT

public:
    explicit CStatusRail12(QWidget *parent = 0);

public slots:
    void OnStatusFresh();       //显示数据刷新
    void OnViewDirChange(int);      //显示视角切换
};

#endif // STATUS_RAIL12_H
