#ifndef INFO_BASE_NDT8_H
#define INFO_BASE_NDT8_H

#include "info_base.h"


class CInfoBaseNdt8 : public CInfoBase
{
    Q_OBJECT
    
public:
    explicit CInfoBaseNdt8(QWidget *parent = 0);

public slots:
    virtual void OnInfoFresh();

};

#endif // INFO_BASE_NDT8_H
