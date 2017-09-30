#ifndef REMOTE_BASE_H
#define REMOTE_BASE_H

#include "system_base.h"
#include <QTcpSocket>

class CRemoteBase : public CSystemBase
{
    Q_OBJECT
    
public:
    explicit CRemoteBase(QWidget *parent = 0);
    
private slots:
    void OnBtnExit();
};

#endif // REMOTE_BASE_H
