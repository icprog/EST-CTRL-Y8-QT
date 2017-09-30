#ifndef STATUS_UARM10_H
#define STATUS_UARM10_H

#include "status_base10.h"


class CStatusUarm10 : public CStatusBase10
{
    Q_OBJECT
    
public:
    explicit CStatusUarm10(QWidget *parent = 0);
    
public slots:
    void OnStatusFresh();   //刷新显示数据

};

#endif // STATUS_UARM10_H
