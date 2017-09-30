#ifndef DEBUG_PAGE2_H
#define DEBUG_PAGE2_H

#include "debug_base.h"


class CDebugPage2 : public CDebugBase
{
    Q_OBJECT
    
public:
    explicit CDebugPage2(int mpf,QWidget *parent = 0);

private:

    CButtonStable * btBack;
    CButtonStable * btTempDec;
    CButtonStable * btTempAdd;

    QLabel  * lbTubeTemp;
    QLabel  * lbTubeTemperature;
    QLabel  * plbWarnning;

    void UpdateSampleData();
    void debugInit(int);
private slots:

    void OnButtonClick();

public slots:
    void OnDebugFresh();

    void OnDebugPressed();
    void OnDebugReleased();

};


#endif // DEBUG_PAGE2_H
