#ifndef SYSTEM_PLATFORM_H
#define SYSTEM_PLATFORM_H
#include <QProcess>

#include "system_defines.h"
#include "system_base.h"
#include "dialog_confirm.h"

class CSystemPlatform : public CSystemBase
{
    Q_OBJECT
    
public:
    explicit CSystemPlatform(QWidget *parent = 0);
    
protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent( QKeyEvent *  );
private:
    QLabel *lbMessage;

private:
    CButtonStable   * pBtnGroup[PLATFORM_MAX];
    CButtonStable *btReboot;

    CDialogConFirm * msgBox;
    QAbstractButton * mBtnYes;
    QAbstractButton * mBtnNo;

    //int m_iPlatformTarget;

    //void PlatformCheck(int , bool);
    void PlatformIndex();
    bool BootBurn(int);
    void BtnPressed(int);

private slots:
    void OnPlatformPressed();
    void OnBtnExit();
    void OnBtnReboot();

public slots:
    void OnPlatformConfirm(QAbstractButton * );
};

#endif // SYSTEM_PLATFORM_H
