#ifndef SMART_CEIL_12_H
#define SMART_CEIL_12_H

#include "./base12/smart_base12.h"

#ifdef USE_CEIL_12_A

class CSmartCeil12a : public CSmartBase12
{
    Q_OBJECT
    
public:
    explicit CSmartCeil12a(QWidget *parent = 0);

protected:
    void OnSelfRunCtrlSoft();   //self run control soft limit,ruan jian xian wei
    void OnSelfRunCtrlHard();   //self run control hard limit,ying jian xian wei
    void OnSelfRunCtrlMach();   //self run control mach limit,ji xie xian wei

public slots:
    void OnSmartChange(int mPos);
};

#endif  //SMART_CEIL_12_H
#endif  //USE_CEIL_12_A
