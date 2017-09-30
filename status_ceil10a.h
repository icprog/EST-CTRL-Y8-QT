#ifndef STATUS_CEIL10_A_H
#define STATUS_CEIL10_A_H

#include "status_base10.h"


class CStatusCeil10a : public CStatusBase10
{
    Q_OBJECT
    
public:
    explicit CStatusCeil10a(QWidget *parent = 0);
    
public slots:
    void OnStatusFresh();       //更新显示数据
};

#endif // STATUS_CEIL10_A_H
