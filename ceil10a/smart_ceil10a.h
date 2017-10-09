#ifndef CEIL10_A_SMART_H
#define CEIL10_A_SMART_H

#include "./base10/smart_base10.h"


class CSmartCeil10a : public CSmartBase10
{
    Q_OBJECT
    
public:
    explicit CSmartCeil10a(QWidget *parent = 0);

public slots:
    void OnSmartChange(int mPos);   //
};

#endif // CEIL10_A_SMART_H
