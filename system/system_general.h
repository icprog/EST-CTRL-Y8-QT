#ifndef SYSTEM_GENERAL_H
#define SYSTEM_GENERAL_H

#include "./base/system_base.h"


class CSystemGeneral : public CSystemBase
{
    Q_OBJECT
    
public:
    explicit CSystemGeneral(QWidget *parent = 0);

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);

private:
    int m_iRebootCount;
    CButtonStable * pBtnGroup[3];
    CButtonStable *btKeySound;
    CButtonStable *btInfoUpdate;

    QFrame *pFrameLine[6];
    QLabel *strCtrl[14];
    QPushButton *btReboot;

    void UpdateClientInfo();

private slots:
    void OnButtonPressed();     /*负责按键声音、皮肤*/
    void OnButtonControl();     /*负责退出、重启*/
    void OnButtonUpdate();      /*更新客户信息*/

};

#endif // SYSTEM_GENERAL_H
