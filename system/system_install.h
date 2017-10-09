#ifndef SYSTEM_INSTALL_H
#define SYSTEM_INSTALL_H

#include "./base/system_base.h"


#define INSTALL_EDIT_MAX        ( 13 )
#define INSTALL_LABEL_MAX        ( 21 )

class CSystemInstall : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemInstall( QWidget* parent = 0);

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:
    QLabel          * sterror;
    CButtonStable   * btStateOn;
    CButtonStable   * btStateOff;
    CButtonStable   * btSave;
    QLabel          * pLineE[INSTALL_EDIT_MAX];
    QLabel          * pLabelAry[INSTALL_LABEL_MAX];

public slots:

    bool eventFilter(QObject *, QEvent *);

    void OnInstallSave();
    void OnInstallExit();
    void OnStateChange();
};

#endif //SYSTEM_INSTALL_H
