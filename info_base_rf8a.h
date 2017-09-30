#ifndef INFO_BASE_RF8A_H
#define INFO_BASE_RF8A_H

#include "info_base.h"


class CInfoBaseRf8a : public CInfoBase
{
    Q_OBJECT
    
public:
    explicit CInfoBaseRf8a(QWidget *parent = 0);

public slots:
    virtual void OnInfoFresh();

};

#endif // INFO_BASE_RF8A_H
