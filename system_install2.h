#ifndef SYSTEM_INSTALL2_H
#define SYSTEM_INSTALL2_H

#include "system_base.h"


class CSystemInstall2 : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemInstall2( QWidget* parent = 0);

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:
    QLabel          * sterror;
    CButtonStable   * btStateOn;
    CButtonStable   * btStateOff;
    CButtonStable   * btSave;

    QList <QLabel*> arrEdit;
    QList <QLabel*> arrLabel;

    QList <QString*> arrPwd;        //old password,
    void FreshInformation();

public slots:

    bool eventFilter(QObject *, QEvent *);

    void OnInstallSave();
    void OnInstallExit();
};

#endif //SYSTEM_INSTALL2_H
