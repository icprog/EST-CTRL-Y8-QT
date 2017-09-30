#ifndef INFO_BASE10_H
#define INFO_BASE10_H

#include "info_base.h"


class CInfoBase10 : public CInfoBase
{
    Q_OBJECT
    
public:
    explicit CInfoBase10(QWidget *parent = 0);

public slots:
    virtual void OnInfoFresh();
};

#endif // INFO_BASE10_H
