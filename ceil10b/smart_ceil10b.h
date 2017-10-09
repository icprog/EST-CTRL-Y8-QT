#ifndef CEIL10_B_SMART_H
#define CEIL10_B_SMART_H

#include "./base10/smart_base10.h"


class CSmartCeil10b : public CSmartBase10
{
    Q_OBJECT
    
public:
    explicit CSmartCeil10b(QWidget *parent = 0);


public slots:
    virtual void OnSmartChange(int mPos);           //
    virtual void OnStatusChange(int);       //Smart状态切换信号槽，用于10寸屏的消息回馈
};

#endif // CEIL10_B_SMART_H
