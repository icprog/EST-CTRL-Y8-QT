#ifndef STATUS_CEIL8_H
#define STATUS_CEIL8_H

#include "status_base8.h"


class CStatusCeil8 : public CStatusBase8
{
    Q_OBJECT
    
public:
    explicit CStatusCeil8(QWidget *parent = 0);

public slots:
    void OnStatusFresh();       //刷新显示数据
    void OnViewDirChange(int);      //显示视角切换
};


#endif // STATUS_CEIL8_H
