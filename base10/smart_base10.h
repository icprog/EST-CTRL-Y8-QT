#ifndef SMART_BASE10_H
#define SMART_BASE10_H

#include "./base/smart_base.h"


class CSmartBase10 : public CSmartBase
{
    Q_OBJECT

public:
    explicit CSmartBase10(QWidget *parent = 0);

protected:
    void OnSelfRunControl();

    int SmartCmdWait();

public slots:
    virtual void OnViewDirChange(int);  //显示视角切换
};

#endif // SMART_BASE10_H
