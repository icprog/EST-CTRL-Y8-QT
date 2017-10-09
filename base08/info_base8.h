#ifndef INFO_BASE8_H
#define INFO_BASE8_H

#include "./base/info_base.h"


class CInfoBase8 : public CInfoBase
{
    Q_OBJECT
    
public:
    explicit CInfoBase8(QWidget *parent = 0);

public slots:
    virtual void OnInfoFresh();

};

#endif // INFO_BASE8_H
