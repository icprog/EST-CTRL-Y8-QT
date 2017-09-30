#ifndef MOTOR_NDT_H
#define MOTOR_NDT_H

#include "system_base.h"

#define NDT_SOFT_LIMIT_NUMBER   11


class CMotorNdt : public CSystemBase
{
    Q_OBJECT
public:
    explicit CMotorNdt(QWidget *parent = 0);
    virtual ~CMotorNdt();

    int getLimitMin(int);
    int getLimitMax(int);
protected:
    void hideEvent(QHideEvent *event);
    void showEvent(QShowEvent *event);

    void mousePressEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *);
    bool eventFilter(QObject *, QEvent *);

    bool loadSoftLimit(QString );      //load soft limit setting from ini file
    bool saveSoftLimit(QString);        //save soft limit setting value to ini file

    bool updateSoftLimit(bool );        //update or store soft limit data;true for display,false for storage
private:

    QLabel      * pLabel[NDT_SOFT_LIMIT_NUMBER];
    QLabel      * pEditNdt[NDT_SOFT_LIMIT_NUMBER * 2];      //include min and max data

    int  m_iMotorSoftMin[NDT_SOFT_LIMIT_NUMBER];
    int  m_iMotorSoftMax[NDT_SOFT_LIMIT_NUMBER];

    QTimer      * timerNdtFresh;
    QFrame    * pFrameLine;
    QLabel      * lbSave;
    QLabel      *lbMax[2];
    QLabel      *lbMin[2];
    CButtonStable* btSave;

public slots:
    void OnBtnNdtPressed();
};

#endif // MOTOR_NDT_H
