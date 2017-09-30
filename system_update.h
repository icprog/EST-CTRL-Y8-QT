#ifndef SYSTEM_UPDATE_H
#define SYSTEM_UPDATE_H

#include <QFile>
#include <QProcess>
#include <QProgressBar>

#include "system_base.h"

#define VERSION_MAX_LENGTH              (5)


class CSystemUpdate : public CSystemBase
{ 
    Q_OBJECT
public:
    CSystemUpdate( QWidget* parent = 0);

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent ( QKeyEvent * event );

private:

    QFrame *frameLine0;
    QFrame *frameLine1;
    QFrame *frameLine2;

    QLabel *TextLabel0;
    QLabel *TextLabel1;
    QLabel *TextLabel2;
    QLabel *TextLabel3;
    QLabel *TextLabel4;     //current firmware version of control board
    QLabel *pixUSB;
    QLabel *strMessage;

    QLabel *edCmd;

    QProgressBar *ProgressCtrl;
    QProgressBar *ProgressConsole;

    CButtonStable *btUpdateControl;
    CButtonStable *btRestart;
    CButtonStable *btUpdateConsole;
    CButtonStable *btCalibration;

private:
    bool    bComm;
    bool    bSending;

    QFile   mfileNewCode;
    long    mfileLenght;

    int nCounters;
    int nSeconds;

    QTimer      * timerUpdate;
    QTimer      * timerCounter;

    void    SendCancel();
    int     check_sda();

    int m_DelayCounter;
public slots:
    bool eventFilter(QObject *, QEvent *);

    void OnButtonConsole(); //Console update
    void OnButtonControl(); //Control update
    void OnButtonUpdate();  //common button

    void OnTimerProgram();
    void OnCounterUpdate();

    void OnUpdateError ( QProcess::ProcessError error );
    void OnUpdateFinished ( int exitCode, QProcess::ExitStatus exitStatus );
};

#endif //SYSTEM_UPDATE_H
