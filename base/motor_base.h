#ifndef MOTOR_BASE_H
#define MOTOR_BASE_H

#include <QWidget>
#include <QLabel>

#include "./system/system_defines.h"
#include "button_stable.h"
#include "./base/system_base.h"

#define MOTOR_CFG_MAX       ( 8 )
#define MOTOR_CMD_MAX       ( 6 )
#define CAL_DATA_MAX        ( 3 )


class CMotorBase : public CSystemBase
{
    Q_OBJECT
    
public:
    CMotorBase(int mPlatform,int motor,QWidget *parent = 0);

    void SetWidgetIndex(QWidget * widNext,QWidget * widBack);

    int DataValidCheck();           //校验保存回读的位置存储数据是否正确

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent ( QKeyEvent * event );
    void keyReleaseEvent ( QKeyEvent * event );

    void SendCmdKey(int);               //发送给下位机的命令
private:
    QLabel *lbSample;
    QLabel *edElectronicScale;

    QLabel *lbMinSave;
    QLabel *lbMaxSave;

    QLabel *lbMinTitle;
    QLabel *lbMinInfo1;
    QLabel *lbMinInfo2;
    QLabel *lbMaxTitle;
    QLabel *lbMaxInfo1;
    QLabel *lbMaxInfo2;

    //QLabel *edPositionMax;
    //QLabel *edPositionMin;

    CButtonStable *btPositionDown;
    CButtonStable *btPositionUp;

    //CButtonStable *btSaveMin;
    //CButtonStable *btSaveMax;

    QList <QObject*> pWidArr;   //0 for editMin,1 for btnMin,2 for edit Max , 3 for BtnMax

    CButtonStable *btBack;
    CButtonStable *btNext;

    QWidget * pWidNext;
    QWidget * pWidBack;

    QTimer* tmDataRefresh;

    int m_iMotorIdx;

    unsigned short m_iIdxCur;
    unsigned short m_iIdxMin;
    unsigned short m_iIdxMax;

    unsigned short m_iComCmd[MOTOR_CFG_MAX][MOTOR_CMD_MAX];
    unsigned short m_iDataIdx[MOTOR_CFG_MAX][CAL_DATA_MAX];

    void InitCeil10aMotor(int motor);                       //初始化为不同的电机
    void InitCeil10bMotor(int motor);                       //初始化为不同的电机
    void InitCeil8Motor(int motor);                         //初始化为不同的电机
    void InitUarm10Motor(int motor);                        //初始化为不同的电机
    void InitUarm8Motor(int motor);                         //初始化为不同的电机
    void InitRail10Motor(int motor);                        //初始化为不同的电机
    void InitRail8Motor(int motor);                         //初始化为不同的电机
    void InitRf8aMotor(int motor);                       //初始化为不同的电机
    void InitNdt8aMotor(int motor);                       //初始化为不同的电机

    void InitCeil10aData();
    void InitCeil10bData();
    void InitCeil8Data();
    void InitUarm10Data();
    void InitUarm8Data();
    void InitRail10Data();
    void InitRail8Data();
    void InitRf8aData();
    void InitNdt8aData();
public slots:

    bool eventFilter(QObject *, QEvent *);

    void OnMotorRefresh();

    void OnButtonPressed();
    void OnButtonReleased();
    void OnBtnClickIndex();
    void OnBtnClickSaveMin();
    void OnBtnClickSaveMax();

};

#endif // MOTOR_BASE_H
