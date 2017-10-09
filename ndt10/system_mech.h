#ifndef CSYSTEMMECH_H
#define CSYSTEMMECH_H

//#include <functional>
#include "./base/system_base.h"
#include "./ndt10/mech_stand.h"
#include "./ndt10/mech_arm.h"
#include "./ndt10/mech_panel.h"
#include "./ndt10/mech_tube.h"
#include "./ndt10/mech_round_table.h"
#include "./ndt10/mech_small_table.h"
#include "./ndt10/mech_long_table.h"
#include "./ndt10/mech_panel_brace.h"

#include <QObject>
#include <QWidget>
#include <QList>
#include <QMap>


class CSystemMech : public CSystemBase
{
public:
    CSystemMech();

    void MechInit();        //init of all mech data

    void MoveLargeRound(int );          //大圆台移动//arLargeRoundMech
    void MoveLongTable(int);              //长台移动//arLongTableMech
    void MoveTube(int,int,int);            //球管移动,X,Y,Z//arTubeMech
    void MoveUarmHeight(int );          //U臂上升下降
    void MovePanelY(int);                    //平板Y方向移动
    void MovePanelRotate(int);           //平板Y方向移动

    void FreshDatas(unsigned short *);      //更新下位机返回的数据到机械参数中
    void CollisionDetect();                     //运行碰撞检测，停止掉可能碰撞的电机

    ////安全检测
    //横臂运动安全检测
    bool isUarmUpSafe();                //横臂上升是否安全
    bool isUarmDownSafe();          //横臂下降是否安全

    //长台运动安全检测
    bool isLongTableLeftSafe();
    bool isLongTableRightSafe();

    //大圆台运动安全检测
    bool isRoundTableLeftSafe();
    bool isRoundTableRightSafe();
    bool isRoundZzSafe();
    bool isRoundFzSafe();

    bool isSmallZzSafe();
    bool isSmallFzSafe();

    //平板移动安全检测
    bool isPanelForwordSafe();          //平板向前，数据减小
    bool isPanelBackwordSafe();         //平板向后，数据增大

    //平板转动安全检测
    bool isPanelTurnVSafe();            //垂直翻转安全性
    bool isPanelTurnHSafe();            //水平翻转安全性

    //球管运动安全检测
    bool isTubeLeftSafe();            //检测球管向左运动是否安全
    bool isTubeRightSafe();          //检测球管向右运动是否安全
    bool isTubeUpSafe();              //检测球管向上运动是否安全
    bool isTubeDownSafe();         //检测球管向下运动是否安全
    bool isTubeForwordSafe();     //检测球管向前运动是否安全
    bool isTubeBackwordSafe();   //检测球管向后运动是否安全
    bool isTubeTurnZzSafe();        //检测球管正转是否安全
    bool isTubeTurnFzSafe();        //检测球管反转是否安全
    void AddAutoCheck(QString);     //添加安全检测函数
    void DelAutoCheck(QString);     //清除安全检测函数

private:

    QMap<QString, int> mAutoCheckList;     //安全检测是，函数对应的数字为1，则进行检查。

    CMechStand              * gMechStand;            //立柱表面对象
    CMechArm                * gMechArm;               //横臂 //x fixed,y fixed,Z move include flat panel and short arm,
    CMechPanel              * gMechPanel;             //flat panel//x fixed,Y by short arm,Z by long arm,rotate arond Y axis
    CMechPanelBrace    * gMechPanelBrace;    //flat panel//x fixed,Y by short arm,Z by long arm,rotate arond Y axis
    CMechTube               * gMechTube;            //tube//X move,Y move,Z move ,rotate around Y axis
    CMechLongTable      * gMechLong;            //long table can move on Y only
    CMechRoundTable   * gMechRound;         //large round table//y,z fixed,can only move on X axis
    CMechSmallTable     * gMechSmall;
};

#endif // CSYSTEMMECH_H
