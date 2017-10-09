#ifndef DEBUG_PAGE1_H
#define DEBUG_PAGE1_H

#include "./base/debug_base.h"
#define BTN_MAX         ( 12 )

#define BRAKE_MAX       ( 2 )
#define BRAKE_A         ( 0 )
#define BRAKE_B         ( 1 )
#define CHANNEL_MAX     (6)

class CDebugPage1 : public CDebugBase
{ 
    Q_OBJECT
public:
    CDebugPage1( int mpf , QWidget* parent = 0);

private:
    CButtonStable * btNext;

    CButtonStable * btDebugCtrl;
    bool    m_bDebugEnable;

    bool    m_bBrakeState[BRAKE_MAX];
    unsigned short pKeycodeBrake[BRAKE_MAX * 2];
    CButtonStable * pBtnBrake[BRAKE_MAX];

    QLabel  * plbMessage[3];

    void UpdateSampleData();
    void InitPlatform(int mpf);

private slots:
    void OnDebug1Click();
    void OnBrakePressed();

public slots:
    void OnDebugFresh();

    void OnDebugPressed();
    void OnDebugReleased();

};

#endif //DEBUG_PAGE1_H
