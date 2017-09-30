#ifndef STATUS_UARM8_H
#define STATUS_UARM8_H

#include "status_base8.h"


class CStatusUarm8 : public CStatusBase8
{
    Q_OBJECT
    
public:
    explicit CStatusUarm8(QWidget *parent = 0);

public slots:
    void OnStatusFresh();           //显示数据刷新
    void OnViewDirChange(int);      //显示视角切换
};

#endif // STATUS_UARM8_H
