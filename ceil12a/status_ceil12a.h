#include "./base12/status_base12.h"
#ifdef USE_CEIL_12_A

#ifndef STATUS_CEIL12_H
#define STATUS_CEIL12_H


class CStatusCeil12a : public CStatusBase12
{
    Q_OBJECT

public:
    explicit CStatusCeil12a(QWidget *parent = 0);

public slots:
    void OnStatusFresh();       //显示数据刷新
};

#endif  //STATUS_CEIL12_H
#endif  //USE_CEIL_12_A
