#ifndef FILM_BASE_H
#define FILM_BASE_H

#include <QWidget>
#include <QSound>
#include <QLabel>

#include "system_base.h"
#include "button_stable.h"
#include "system_defines.h"

#define FILM_KEY_MAX    12
#define FILM_KEY_0031   0
#define FILM_KEY_0032   1
#define FILM_KEY_0033   2
#define FILM_KEY_1012   3
#define FILM_KEY_1030   4
#define FILM_KEY_1031   5
#define FILM_KEY_1032   6
#define FILM_KEY_1036   7
#define FILM_KEY_2030   8
#define FILM_KEY_2031   9
#define FILM_KEY_2032   10
#define FILM_KEY_2033   11

//1.扫描物理按键，发送键码
//2.按键测试控制，显示按键键码
class CFilmBase : public CSystemBase
{
    Q_OBJECT
public:
    explicit CFilmBase(QWidget *parent = 0);

    void SetLCD(bool bState);   //控制LCD
    void SetKeySound();         //发出按键声音

public:
    void filmTask();

    void filmImport(unsigned short);  //扫描物理按键，薄膜按键,扫描任务

    virtual void filmLed(int led = 0);                 //控制物理按键灯显示，控制任务
    int gLedBuffer;
    void filmCtrl(int en);          //控制物理按键允许与禁止

private:
    unsigned short filmScan();   //扫描物理按键，薄膜按键,扫描任务
    void filmKeyExecute(unsigned short);      //扫描键码并发送执行

    int m_iFilmState;           //0停止按键扫描；1允许按键扫描

protected:
    void hideEvent(QHideEvent *);
    void showEvent(QShowEvent *);
    void keyPressEvent( QKeyEvent *  );
    void mousePressEvent(QMouseEvent *);

    virtual void SendCmdKey(int);               //发送给下位机的命令
    virtual void filmKeyDisplay(unsigned short);      //扫描键码仅显示

protected:

    QFrame  * line_1;           //分割线

    QLabel *label_test;         //Key Test:
    QLabel *label_config;       //Configuration:
    QLabel *label_cur_code;     //Physical Key Code:
    QLabel *label_fun_up;       //Key Function Up:
    QLabel *label_fun_down;     //Key Function Down:

    QLabel *lbCurrentCode;      //当前物理键码
    QLabel *lbFunctionUp;       //按键抬起键码
    QLabel *lbFunctionDown;     //按键按下键码

    QTimer * timerFilmLong;     //延时按键检测
    QTimer * timerSoundPlay;    //延时按键检测
    int m_keyTag;               //tag

public:
    int m_keyMax;
    int (*g_keyPtr)[SYS_KEY_MAX][2];

    unsigned short  keylast;
    int             nKey;
    QString mStrBuf;
    unsigned short m_bufLed[8];
    unsigned short m_ledCounter;

private:

    CButtonStable *m_btnKeyFunc[FILM_KEY_MAX];
    int m_btnKeyFiltered[FILM_KEY_MAX];

    int mBufKeyConst[FILM_KEY_MAX];     //常量
    int m_keyFilter[FILM_KEY_MAX];      //需要屏蔽的键码
    int m_keyFilterCount;               //需要屏蔽的按键数量
    int m_bLastKeyFiltered;             //标记、上一个按键被过滤掉
    void KeyFilterInit();               //初始化按键屏蔽功能
    void KeyFilterAdd(int);             //添加需要屏蔽的按键
    void KeyFilterDel(int);             //删除需要屏蔽的按键

protected:
    int             m_fileDevice;
private:
    int             m_fileKeyBoard;

    bool            m_bIsVisable;

    void InitFilmBoard();           //初始化

    QSound * soundKey;

    //QSoundEffect soundKey2;

    void OnKeyFilterSave(int);
private slots:
    void OnFilmExit();              //退出显示界面
    void PlayKeySound();            //由定时器完成声音播放
    void OnKeyFilterDown();         //按键屏蔽处理函数

signals:
    void SmartChange(int);
    void FilmKeyDown(int);
    void FilmKeyUp(int);
};

#endif // FILM_BASE_H
