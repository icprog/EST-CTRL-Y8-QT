#ifndef CEIL8_SMART_H
#define CEIL8_SMART_H

#include "smart_base8.h"


class CSmartCeil8 : public CSmartBase8
{
    Q_OBJECT
    
public:
    explicit CSmartCeil8(QWidget *parent = 0);

private:
    void OnSmartChange00(int mPos);     //老版本协议，支持2个一键位置通道
    void OnSmartChange01(int mPos);     //新版本协议，支持8个一键位置通道

protected:
    void OnSelfRunControl();
    int SmartCmdWait();         //等待一键动作执行完毕,返回1：当前命令完成，有后续命令，0：当前命令完成，无后续命令，-1：当前命令未完成

public slots:
    void OnSmartChange(int mPos);
};

#endif // CEIL8_SMART_H
