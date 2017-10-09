#ifndef STATUS_CEIL10_B_H
#define STATUS_CEIL10_B_H

#include "./base10/status_base10.h"


class CStatusCeil10b : public CStatusBase10
{
    Q_OBJECT
    
public:
    explicit CStatusCeil10b(QWidget *parent = 0);
    
public slots:
    void OnStatusFresh();       //刷新显示数据
};

#endif // STATUS_CEIL10_B_H
