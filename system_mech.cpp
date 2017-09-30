#include "system_mech.h"
#include "system_defines.h"
#include "resource_manager.h"
#include "main_base_ndt10.h"

#include <qmath.h>
#include <QDebug>
#include <QSettings>

//安全距离等级
#define NDT_SAFE_DIATANCE_50          50
#define NDT_SAFE_DIATANCE_70          70
#define NDT_SAFE_DIATANCE_100        100
#define NDT_SAFE_DIATANCE_150        150
#define NDT_SAFE_DIATANCE_200        200
#define NDT_SAFE_DIATANCE_250        250
#define NDT_SAFE_DIATANCE_300        300

CSystemMech::CSystemMech()
{

    MechInit();
}

void CSystemMech::MechInit()
{

    QSettings *pNdtCfg = new QSettings(QCoreApplication::applicationDirPath() + "/ndtConfig.ini",QSettings::IniFormat);
    int mTempX,mTempY,mTempZ;
    //////////////////////////stand

    ////长台//////////////////////Long table init
    gMechLong = new CMechLongTable();

    //x direction;y direction;z direction
    mTempX = pNdtCfg->value("MechSize/LongTableSizeX").toInt();
    mTempY = pNdtCfg->value("MechSize/LongTableSizeY").toInt();
    mTempZ = pNdtCfg->value("MechSize/LongTableSizeZ").toInt();
    gMechLong->setDimension(mTempX,mTempY,mTempZ);

    //x direction;y direction;z direction height of centor
    mTempX = pNdtCfg->value("MechSize/LongTablePosX").toInt();
    mTempY = pNdtCfg->value("MechSize/LongTablePosY").toInt();
    mTempZ = pNdtCfg->value("MechSize/LongTablePosZ").toInt();
    gMechLong->setMechCentor(mTempX,mTempY,mTempZ);

    //构建表面
    gMechLong->BuildSurface();

    ////横臂/////
    gMechArm = new CMechArm();

    mTempX = pNdtCfg->value("MechSize/ArmSizeX").toInt();
    mTempY = pNdtCfg->value("MechSize/ArmSizeY").toInt();
    mTempZ = pNdtCfg->value("MechSize/ArmSizeZ").toInt();
    gMechArm->setDimension(mTempX,mTempY,mTempZ);

    mTempX = pNdtCfg->value("MechSize/ArmPosX").toInt();
    mTempY = pNdtCfg->value("MechSize/ArmPosY").toInt();
    mTempZ = pNdtCfg->value("MechSize/ArmPosZ").toInt();
    gMechArm->setMechCentor(mTempX,mTempY,mTempZ);

    gMechArm->BuildSurface();

    ///平板/////////////////////////////////Long arm
    gMechPanel = new CMechPanel();

    //x direction;y direction;z direction
    mTempX = pNdtCfg->value("MechSize/PanelSizeX").toInt();
    mTempY = pNdtCfg->value("MechSize/PanelSizeY").toInt();
    mTempZ = pNdtCfg->value("MechSize/PanelSizeZ").toInt();
    gMechPanel->setDimension(mTempX,mTempY,mTempZ);

    //x direction;y direction;z direction height of centor
    mTempX = pNdtCfg->value("MechSize/PanelPosX").toInt();
    mTempY = pNdtCfg->value("MechSize/PanelPosY").toInt();
    mTempZ = pNdtCfg->value("MechSize/PanelPosZ").toInt();
    gMechPanel->setMechCentor(mTempX,mTempY,mTempZ);

    gMechPanel->BuildSurface();

    gMechPanelBrace = new CMechPanelBrace();

    //x direction;y direction;z direction
    mTempX = pNdtCfg->value("MechSize/PanelBraceSizeX").toInt();
    mTempY = pNdtCfg->value("MechSize/PanelBraceSizeY").toInt();
    mTempZ = pNdtCfg->value("MechSize/PanelBraceSizeZ").toInt();
    gMechPanelBrace->setDimension(mTempX,mTempY,mTempZ);

    //x direction;y direction;z direction height of centor
    mTempX = pNdtCfg->value("MechSize/PanelBracePosX").toInt();
    mTempY = pNdtCfg->value("MechSize/PanelBracePosY").toInt();
    mTempZ = pNdtCfg->value("MechSize/PanelBracePosZ").toInt();
    gMechPanelBrace->setMechCentor(mTempX,mTempY,mTempZ);

    gMechPanelBrace->BuildSurface();

    ////////////////////////////////////large round table,大圆台
    gMechRound = new CMechRoundTable();

    //x direction;y direction;z direction
    mTempX = pNdtCfg->value("MechSize/LRoundSizeX").toInt();
    mTempY = pNdtCfg->value("MechSize/LRoundSizeY").toInt();
    mTempZ = pNdtCfg->value("MechSize/LRoundSizeZ").toInt();
    gMechRound->setDimension(mTempX,mTempY,mTempZ);

    //x direction;y direction;z direction height of centor
    mTempX = pNdtCfg->value("MechSize/LRoundPosX").toInt();
    mTempY = pNdtCfg->value("MechSize/LRoundPosY").toInt();
    mTempZ = pNdtCfg->value("MechSize/LRoundPosZ").toInt();
    gMechRound->setMechCentor(mTempX,mTempY,mTempZ);

    gMechRound->BuildSurface();

    //////////////////////////////////////tube

    gMechTube = new CMechTube();

    //x direction;y direction;z direction
    mTempX = pNdtCfg->value("MechSize/TubeSizeX").toInt();
    mTempY = pNdtCfg->value("MechSize/TubeSizeY").toInt();
    mTempZ = pNdtCfg->value("MechSize/TubeSizeZ").toInt();
    gMechTube->setDimension(mTempX,mTempY,mTempZ);

    //x direction;y direction;z direction height of centor
    mTempX = pNdtCfg->value("MechSize/TubePosX").toInt();
    mTempY = pNdtCfg->value("MechSize/TubePosY").toInt();
    mTempZ = pNdtCfg->value("MechSize/TubePosZ").toInt();
    gMechTube->setMechCentor(0,0,0);

    gMechTube->BuildSurface();

    /////立柱/////////////////////////////////tube

    gMechStand = new CMechStand();

    //x direction;y direction;z direction
    mTempX = pNdtCfg->value("MechSize/StandSizeX").toInt();
    mTempY = pNdtCfg->value("MechSize/StandSizeY").toInt();
    mTempZ = pNdtCfg->value("MechSize/StandSizeZ").toInt();
    gMechStand->setDimension(mTempX,mTempY,mTempZ);

    //x direction;y direction;z direction height of centor
    mTempX = pNdtCfg->value("MechSize/StandPosX").toInt();
    mTempY = pNdtCfg->value("MechSize/StandPosY").toInt();
    mTempZ = pNdtCfg->value("MechSize/StandPosZ").toInt();
    gMechStand->setMechCentor(mTempX,mTempY,mTempZ);

    gMechStand->BuildSurface();

    /////小圆台/////////////////主要避免被球管撞
    gMechSmall = new CMechSmallTable();

    //x direction;y direction;z direction
    mTempX = pNdtCfg->value("MechSize/SmallSizeX",0).toInt();
    mTempY = pNdtCfg->value("MechSize/SmallSizeY",0).toInt();
    mTempZ = pNdtCfg->value("MechSize/SmallSizeZ",0).toInt();
    gMechSmall->setDimension(mTempX,mTempY,mTempZ);

    //x direction;y direction;z direction height of centor
    mTempX = pNdtCfg->value("MechSize/SmallPosX",0).toInt();
    mTempY = pNdtCfg->value("MechSize/SmallPosY",0).toInt();
    mTempZ = pNdtCfg->value("MechSize/SmallPosZ",0).toInt();
    gMechSmall->setMechCentor(mTempX,mTempY,mTempZ);

    gMechSmall->BuildSurface();

}
void CSystemMech::FreshDatas(unsigned short * pNdtData)
{

    //球管移动
    MoveTube(pNdtData[NDT_KEY_IDX_SID],pNdtData[NDT_KEY_IDX_CEP],pNdtData[NDT_KEY_IDX_FID]);

    //平板转动
    MovePanelRotate(pNdtData[NDT_KEY_IDX_DTA]);

    //U臂移动
    MovePanelY(pNdtData[ NDT_KEY_IDX_UID]);
    MoveUarmHeight(pNdtData[ NDT_KEY_IDX_HEI]);

    //长台移动
    MoveLongTable(pNdtData[ NDT_KEY_IDX_LMV]);

    //大园台移动
    MoveLargeRound(pNdtData[ NDT_KEY_IDX_RMV]);

    gMechSmall->SaveMechPointsReal();
}


//添加运动碰撞检测
void CSystemMech::AddAutoCheck(QString func)
{
    mAutoCheckList.insert(func,true);
}

//清除运动碰撞检测
void CSystemMech::DelAutoCheck(QString func)
{
    mAutoCheckList.insert(func,false);
}

//移动大圆台
void CSystemMech::MoveLargeRound(int mXPos)
{
    gMechRound->MoveX(mXPos);
    gMechRound->SaveMechPointsReal();
}

//移动长台
void CSystemMech::MoveLongTable(int mXPos)
{
    gMechLong->MoveX(mXPos);
    gMechLong->SaveMechPointsReal();

}

//移动球管
void CSystemMech::MoveTube(int mXPos,int mYPos,int mZPos)
{
    gMechTube->MoveXYZ(mXPos,mYPos,mZPos);

    gMechTube->SaveMechPointsReal();
}

//移动横臂高度
void CSystemMech::MoveUarmHeight(int mZPos)
{
    //更新长台Z方向数据
    gMechArm->MoveZ(mZPos);

    //打印长台数据
    gMechArm->SaveMechPointsReal();

    gMechPanelBrace->MoveZ(mZPos);

    gMechPanelBrace->SaveMechPointsReal();
    //更新平板高度
    gMechPanel->MoveZ(mZPos);

    //打印平板数据
    gMechPanel->SaveMechPointsReal();

}

//平板前后数据更新
void CSystemMech::MovePanelY(int mYPos)
{
    gMechPanel->MoveY(mYPos);

    gMechPanelBrace->MoveY(mYPos);
}

//平板转动
void CSystemMech::MovePanelRotate(int mAng)
{
    //arFlatPanelMech
    gMechPanel->setAngle(mAng);
}

///1.//检测球管向上运动是否安全
bool CSystemMech::isTubeUpSafe()
{
    //default safe
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);
    pNdtBase->SetWarningText("");

    return true;
}
///1.//检测球管向下运动是否安全
bool CSystemMech::isTubeDownSafe()
{

    bool UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //检测不能与长台相撞
    if(gMechTube->getXMin() - gMechLong->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getYMin() - gMechLong->getYMax() < NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechLong->getZ() < NDT_SAFE_DIATANCE_200)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Long Table");
        return false;
    }

    //检测不能与大圆台相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechRound->getXMin() - gMechTube->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechRound->getYMin() - gMechTube->getYMax() < NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechRound->getZ() < NDT_SAFE_DIATANCE_70)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Round Table");
        return false;
    }

    //检测不能与小圆台相撞
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if( gMechTube->getXMin() >= gMechSmall->getXMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getXMin() <= gMechSmall->getXMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if( gMechTube->getXMax() >= gMechSmall->getXMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getXMax() <= gMechSmall->getXMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if( gMechTube->getYMin() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getYMin() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechTube->getYMax() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getYMax() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechTube->getZMin()  <= gMechSmall->getZMax() + NDT_SAFE_DIATANCE_100 )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Small Table");
        return false;
    }

    //检测不能与平板相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechPanel->getXMin() >  gMechTube->getXMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getXMin() < gMechTube->getXMax() + NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if(gMechPanel->getXMax() >  gMechTube->getXMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getXMax() < gMechTube->getXMax() + NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if(gMechPanel->getYMin() >  gMechTube->getYMin() - NDT_SAFE_DIATANCE_100 && gMechPanel->getYMin() < gMechTube->getYMax() + NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechPanel->getYMax() >  gMechTube->getYMin() - NDT_SAFE_DIATANCE_100 && gMechPanel->getYMax() < gMechTube->getYMax() + NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechPanel->getZMax() < NDT_SAFE_DIATANCE_250)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Panel");
        return false;
    }

    //检测不能与横臂相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechTube->getXMin() - gMechArm->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    UnSafeY = true;

    if(gMechTube->getZMin() - gMechArm->getZMax() < NDT_SAFE_DIATANCE_200)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Arm");
        return false;
    }

    pNdtBase->SetWarningText("");
    return true;
}

///2.//检测球管向左运动是否安全
bool CSystemMech::isTubeLeftSafe()
{
    //初始化变量
    bool UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //不能与长台相撞
    if(gMechTube->getXMin() - gMechLong->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getYMin() - gMechLong->getYMax() < NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechLong->getZMax() < NDT_SAFE_DIATANCE_100)
        UnSafeZ = true;

    if( UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Long Table");
        return false;
    }

    //不能与横臂相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechTube->getXMin() - gMechArm->getXMax() < NDT_SAFE_DIATANCE_200)
        UnSafeX = true;

    UnSafeY = true;

    if(gMechTube->getZMin() - gMechArm->getZMax() < NDT_SAFE_DIATANCE_150)
        UnSafeZ = true;

    if( UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Arm");
        return false;
    }

    //不能与立柱相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;

    if(gMechTube->getXMin() - gMechStand->getXMax() < 0)
        UnSafeX = true;

    if( gMechStand->getYMin() -  gMechTube->getYMax() < NDT_SAFE_DIATANCE_50)
        UnSafeY = true;

    if( UnSafeX && UnSafeY)
    {
        pNdtBase->SetWarningText("Tube Near to Stand");
        return false;
    }

    //不能与平板相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechTube->getXMin() - gMechPanel->getXMax() < NDT_SAFE_DIATANCE_100 )
        UnSafeX = true;

    if(gMechTube->getYMin()  > gMechPanel->getYMin() - NDT_SAFE_DIATANCE_150 && gMechTube->getYMin()  < gMechPanel->getYMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeY = true;

    if(gMechTube->getYMax()  > gMechPanel->getYMin() - NDT_SAFE_DIATANCE_150 && gMechTube->getYMin()  < gMechPanel->getYMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeY = true;

    if(gMechTube->getZ() - gMechPanel->getZMax() < NDT_SAFE_DIATANCE_200)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Panel");
        return false;
    }

    //检测不能与小圆台相撞
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;

    if( gMechTube->getYMin() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getYMin() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechTube->getYMax() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getYMax() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechTube->getZMin()  <= gMechSmall->getZMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeZ = true;

    if(UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Small Table");
        return false;
    }

    pNdtBase->SetWarningText("");
    return true;
}
///2.//检测球管向右运动是否安全
bool CSystemMech::isTubeRightSafe()
{
    bool UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //不能与平板相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechTube->getXMax() <  gMechPanel->getXMin() - NDT_SAFE_DIATANCE_100 )
        UnSafeX = true;

    if(gMechTube->getYMin() - gMechPanel->getYMax() < NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechPanel->getZMax() < NDT_SAFE_DIATANCE_150)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Panel");
        return false;
    }

    //不能与大圆台相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechRound->getXMin() - gMechTube->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getYMin() > gMechRound->getYMin() - NDT_SAFE_DIATANCE_150 && gMechTube->getYMin() < gMechRound->getYMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeY = true;

    if(gMechTube->getYMax() > gMechRound->getYMin() - NDT_SAFE_DIATANCE_150 && gMechTube->getYMax() < gMechRound->getYMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechRound->getZMax() < NDT_SAFE_DIATANCE_200)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Round Table");
        return false;
    }

    pNdtBase->SetWarningText("");
    return true;
}
///检测球管向前运动是否安全
///3.//检测球管正转是否安全
bool CSystemMech::isTubeTurnZzSafe()
{
    return true;
}
//检测球管反转是否安全
bool CSystemMech::isTubeTurnFzSafe()
{
    return true;
}
///4.//球管前后是否安全
bool CSystemMech::isTubeForwordSafe()
{
    bool UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //不能与平板相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechTube->getXMin() - gMechPanel->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getYMin()   - gMechPanel->getYMax() < NDT_SAFE_DIATANCE_200)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechPanel->getZMax() < NDT_SAFE_DIATANCE_100)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Panel");
        return false;
    }

    //不能与大圆台相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;

    if(gMechRound->getXMin() - gMechTube->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getYMin() > gMechRound->getYMin() - NDT_SAFE_DIATANCE_150 && gMechTube->getYMin() < gMechRound->getYMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeY = true;

    if(gMechTube->getYMax() > gMechRound->getYMin() - NDT_SAFE_DIATANCE_150 && gMechTube->getYMax() < gMechRound->getYMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechRound->getZMax() < NDT_SAFE_DIATANCE_70)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Round Table");
        return false;
    }

    //不能与小圆台相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if( gMechTube->getYMin() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getYMin() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if( gMechTube->getYMax() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getYMax() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if( gMechTube->getYMin() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_150 && gMechTube->getYMin() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeY = true;

    if( gMechTube->getYMax() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_150 && gMechTube->getYMax() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeY = true;

    if( gMechTube->getZMin()  <= gMechSmall->getZMax() + NDT_SAFE_DIATANCE_100 )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Small Table");
        return false;
    }

    pNdtBase->SetWarningText("");
    return true;
}
///检测球管向后运动是否安全
bool CSystemMech::isTubeBackwordSafe()
{
    bool UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //不能与平板相撞
    if(gMechTube->getXMin() - gMechPanel->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getYMax() - gMechPanel->getYMin()  < NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechPanel->getZMax() < NDT_SAFE_DIATANCE_100)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Panel");
        return false;
    }

    //不能与大圆台相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;

    if(gMechRound->getXMin() - gMechTube->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getYMin() > gMechRound->getYMin() - NDT_SAFE_DIATANCE_150 && gMechTube->getYMin() < gMechRound->getYMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeY = true;

    if(gMechTube->getYMax() > gMechRound->getYMin() - NDT_SAFE_DIATANCE_150 && gMechTube->getYMax() < gMechRound->getYMax() + NDT_SAFE_DIATANCE_150 )
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechRound->getZMax() < NDT_SAFE_DIATANCE_200)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Round Table");
        return false;
    }

    //不能与小圆台相撞
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;

    if( gMechTube->getYMin() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getYMin() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if( gMechTube->getYMax() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getYMax() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if( gMechTube->getYMin() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getYMin() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechTube->getYMax() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechTube->getYMax() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechTube->getZMin()  <= gMechSmall->getZMax() + NDT_SAFE_DIATANCE_200 )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Tube Near to Small Table");
        return false;
    }

    //不能与立柱相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;

    if(gMechTube->getXMin() - gMechStand->getXMax() < 0)
        UnSafeX = true;

    if( gMechStand->getYMin() -  gMechTube->getYMax() < NDT_SAFE_DIATANCE_50)
        UnSafeY = true;

    if( UnSafeX && UnSafeY)
    {
        pNdtBase->SetWarningText("Tube Near to Stand");
        return false;
    }

    pNdtBase->SetWarningText("");
    return true;
}
///5.//平板前后是否安全
bool CSystemMech::isPanelForwordSafe()
{

    bool UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //不能与大圆台相撞
    if(gMechRound->getXMin() - gMechPanel->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if( gMechRound->getYMin() >= gMechPanel->getYMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getYMin() <= gMechPanel->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechRound->getYMax() >= gMechPanel->getYMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getYMax() <= gMechPanel->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechRound->getZ() >= gMechPanel->getZMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getZ() <= gMechPanel->getZMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Round Table");
        return false;
    }

    //不能与球管相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechTube->getXMin() > gMechPanel->getXMin() - NDT_SAFE_DIATANCE_100 && gMechTube->getXMin() < gMechPanel->getXMax() + NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getXMin() > gMechPanel->getXMin() - NDT_SAFE_DIATANCE_100 && gMechTube->getXMin() < gMechPanel->getXMax() + NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechPanel->getYMin() > gMechTube->getYMax() + NDT_SAFE_DIATANCE_150)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechPanel->getZMax() < NDT_SAFE_DIATANCE_150)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Tube");
        return false;
    }

    //不能与长台相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;

    if(gMechPanel->getXMin() >= gMechLong->getXMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getXMin() <= gMechLong->getXMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if(gMechPanel->getXMax() >= gMechLong->getXMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getXMax() <= gMechLong->getXMax() + NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if(gMechPanel->getYMin()  <= gMechLong->getYMax()   + NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechLong->getZ() >= (gMechPanel->getZMin() - NDT_SAFE_DIATANCE_50)  && gMechLong->getZ() <= (gMechPanel->getZMax() + NDT_SAFE_DIATANCE_50) )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Long Table");
        return false;
    }

    pNdtBase->SetWarningText("");

    return true;
}
bool CSystemMech::isPanelBackwordSafe()
{
    bool UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //不能与大圆台相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechRound->getXMin() - gMechPanel->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if( gMechRound->getYMin() >= gMechPanel->getYMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getYMin() <= gMechPanel->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechRound->getYMax() >= gMechPanel->getYMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getYMax() <= gMechPanel->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechRound->getZ() >= gMechPanel->getZMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getZ() <= gMechPanel->getZMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Round Table");
        return false;
    }

    //不能与球管相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechTube->getXMin() > gMechPanel->getXMin() - NDT_SAFE_DIATANCE_100 && gMechTube->getXMin() < gMechPanel->getXMax() + NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getXMin() > gMechPanel->getXMin() - NDT_SAFE_DIATANCE_100 && gMechTube->getXMin() < gMechPanel->getXMax() + NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getYMin() - gMechPanel->getYMax() < NDT_SAFE_DIATANCE_150)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechPanel->getZMax() < NDT_SAFE_DIATANCE_150)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Tube");
        return false;
    }

    //不能与长台相撞 //认为平板向后不会与长台相撞，不做检测

    pNdtBase->SetWarningText("");

    return true;
}

///6.//平板转动是否安全
/// 垂直翻转安全性
bool CSystemMech::isPanelTurnVSafe()
{
    bool UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    int mSafeDistance;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //不能与球管相撞
    if( gMechPanel->getXMin() >= gMechTube->getXMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getXMin() <= gMechTube->getXMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if( gMechPanel->getXMax() >= gMechTube->getXMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getXMax() <= gMechTube->getXMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if( gMechPanel->getYMin() >= gMechTube->getYMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getYMin() <= gMechTube->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechPanel->getYMax() >= gMechTube->getYMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getYMax() <= gMechTube->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if(gMechPanel->getZMax() > gMechTube->getZMin() - NDT_SAFE_DIATANCE_150)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ )
    {
        pNdtBase->SetWarningText("Panel Near to Tube");
        return false;
    }

    //不能与大圆台相撞
    /*
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechRound->getXMin() - gMechPanel->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if( gMechRound->getYMin() >= gMechPanel->getYMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getYMin() <= gMechPanel->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechRound->getYMax() >= gMechPanel->getYMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getYMax() <= gMechPanel->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechRound->getZ() >= gMechPanel->getZMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getZ() <= gMechPanel->getZMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Round Table");
        return false;
    }
    */

    mSafeDistance = gMechPanel->getDistanceMin(gMechRound);
    //qDebug()<<"Panel and Table ="<<mSafeDistance;

    if(mSafeDistance < 30)
    {
        pNdtBase->SetWarningText("Panel Near to Round Table");
        return false;
    }

    //不能与小圆台相撞
    /*
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechSmall->getXMin() - gMechPanel->getXMax() < NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if( gMechPanel->getYMin() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getYMin() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechPanel->getYMax() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getYMax() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechSmall->getZ() >= gMechPanel->getZMin() - NDT_SAFE_DIATANCE_50 && gMechSmall->getZ() <= gMechPanel->getZMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Small Table");
        return false;
    }
    */

    //不能与长台相撞
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechPanel->getXMin() - gMechLong->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechPanel->getYMin() - gMechLong->getYMax() < NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    //   if(gMechLong->getZ() < gMechPanel->getZMax() + NDT_SAFE_DIATANCE_50 && gMechLong->getZ() > gMechPanel->getZMin() - NDT_SAFE_DIATANCE_50)
    //       UnSafeZ = true;

    if(gMechPanel->getZMin() - gMechLong->getZMax() < NDT_SAFE_DIATANCE_100)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY  && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Long Table");
        return false;
    }

    pNdtBase->SetWarningText("");

    return true;
}
//水平翻转安全性
bool CSystemMech::isPanelTurnHSafe()
{
    bool UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    int mSafeDistance;

    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //不能与球管相撞
    if( gMechPanel->getXMin() >= gMechTube->getXMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getXMin() <= gMechTube->getXMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if( gMechPanel->getXMax() >= gMechTube->getXMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getXMax() <= gMechTube->getXMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeX = true;

    if( gMechPanel->getYMin() >= gMechTube->getYMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getYMin() <= gMechTube->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechPanel->getYMax() >= gMechTube->getYMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getYMax() <= gMechTube->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if(gMechPanel->getZMax() > gMechTube->getZMin() - NDT_SAFE_DIATANCE_200)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ )
    {
        pNdtBase->SetWarningText("Panel Near to Tube");
        return false;
    }

    //不能与大圆台相撞
    /*
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechRound->getXMin() - gMechPanel->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if( gMechPanel->getYMin() >= gMechPanel->getYMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getYMin() <= gMechPanel->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechPanel->getYMax() >= gMechPanel->getYMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getYMax() <= gMechPanel->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechRound->getZ() >= gMechPanel->getZMin() - NDT_SAFE_DIATANCE_50 && gMechRound->getZ() <= gMechPanel->getZMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Round Table");
        return false;
    }
    */

    mSafeDistance = gMechPanel->getDistanceMin(gMechRound);
    //qDebug()<<"Panel and Table ="<<mSafeDistance;

    if(mSafeDistance < 30)
    {
        pNdtBase->SetWarningText("Panel Near to Round Table");
        return false;
    }

    //不能与小圆台相撞
    /*
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechSmall->getXMin() - gMechPanel->getXMax() < NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if( gMechPanel->getYMin() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getYMin() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechPanel->getYMax() >= gMechSmall->getYMin() - NDT_SAFE_DIATANCE_50 && gMechPanel->getYMax() <= gMechSmall->getYMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeY = true;

    if( gMechSmall->getZ() >= gMechPanel->getZMin() - NDT_SAFE_DIATANCE_50 && gMechSmall->getZ() <= gMechPanel->getZMax() + NDT_SAFE_DIATANCE_50 )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Small Table");
        return false;
    }
    */

    //不能与长台相撞
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechPanel->getXMin() - gMechLong->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechPanel->getYMin() - gMechLong->getYMax() < NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechLong->getZ() < gMechPanel->getZMax() + NDT_SAFE_DIATANCE_50 && gMechLong->getZ() > gMechPanel->getZMin() - NDT_SAFE_DIATANCE_50)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY  && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Long Table");
        return false;
    }

    pNdtBase->SetWarningText("");
    return true;
}

///9.//长台移动是否安全
bool CSystemMech::isLongTableLeftSafe()
{
    //目前默认长台向左是安全的
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);
    pNdtBase->SetWarningText("");
    return true;
}
bool CSystemMech::isLongTableRightSafe()
{
    bool UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //不会和横臂相撞
    if(gMechArm->getXMin() - gMechLong->getXMax() < NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if(qAbs(gMechArm->getZ() - gMechLong->getZ()) < NDT_SAFE_DIATANCE_100)
        UnSafeZ = true;

    if( UnSafeX && UnSafeZ)
    {
        pNdtBase->SetWarningText("Long Near to Arm");
        return false;
    }

    //不会和平板相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;

    if(gMechPanel->getXMin() - gMechLong->getXMax() < NDT_SAFE_DIATANCE_200)
        UnSafeX = true;

    if(gMechPanel->getYMin() - gMechLong->getYMax() <  NDT_SAFE_DIATANCE_50)
        UnSafeY = true;

    if(gMechLong->getZ() <=  (gMechPanel->getZMax() + NDT_SAFE_DIATANCE_50) && gMechLong->getZ() >= (gMechPanel->getZMin() - NDT_SAFE_DIATANCE_50))
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Long Near to Panel");
        return false;
    }

    //不能和球管相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if( gMechTube->getXMin() - gMechLong->getXMax() <= NDT_SAFE_DIATANCE_100 )
        UnSafeX = true;

    if( gMechTube->getYMin() - gMechLong->getYMax() <= NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechTube->getZMin()  - gMechLong->getZMax() <= NDT_SAFE_DIATANCE_200)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ )
    {
        pNdtBase->SetWarningText("Long Near to Tube");
        return false;
    }

    //不会和平板支撑相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if( gMechLong->getXMin() - gMechPanelBrace->getXMax() <= NDT_SAFE_DIATANCE_100 )
        UnSafeX = true;

    if( gMechPanelBrace->getYMin() - gMechLong->getYMax() <= NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechLong->getZ() <= gMechPanelBrace->getZMax() + NDT_SAFE_DIATANCE_100 && gMechLong->getZ() >= gMechPanelBrace->getZMin() - NDT_SAFE_DIATANCE_100)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ )
    {
        pNdtBase->SetWarningText("Long Near to Arm");
        return false;
    }

    pNdtBase->SetWarningText("");
    return true;
}
///10.//大圆台移动是否安全
bool CSystemMech::isRoundZzSafe()
{
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    pNdtBase->SetWarningText("");
    return true;
}
bool CSystemMech::isRoundFzSafe()
{
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    pNdtBase->SetWarningText("");
    return true;
}
bool CSystemMech::isRoundTableLeftSafe()
{
    //检测大圆台与平板的安全距离

    bool UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    /*
    if(gMechRound->getXMin() - gMechPanel->getXMax() <= NDT_SAFE_DIATANCE_50)
        UnSafeX  = true;

    if(gMechPanel->getZMin() <= gMechRound->getZ() && gMechRound->getZ()  <= gMechPanel->getZMax())
        UnSafeZ  = true;

    if( gMechRound->getY() - gMechPanel->getYMax() < 600 )
        UnSafeY  = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Round Near to Panel");
        return false;
    }
    */
    int mSafeDistance;
    mSafeDistance = gMechPanel->getDistanceMin(gMechRound);
    //qDebug()<<"Panel and Table ="<<mSafeDistance;

    if(mSafeDistance < 20)
    {
        pNdtBase->SetWarningText("Panel Near to Round Table");
        return false;
    }

    //检测大圆台与球管安全距离
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if(gMechTube->getX() < (gMechRound->getXMax() + NDT_SAFE_DIATANCE_100) && gMechTube->getX() > (gMechRound->getXMin() - NDT_SAFE_DIATANCE_100) )
        UnSafeX = true;

    if(gMechRound->getYMin() - gMechTube->getYMax() < NDT_SAFE_DIATANCE_150)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechRound->getZMax() < NDT_SAFE_DIATANCE_150)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Round Near to Tube");
        return false;
    }

    pNdtBase->SetWarningText("");
    return true;
}
bool CSystemMech::isRoundTableRightSafe()
{
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //检测大圆台与球管安全距离
    pNdtBase->SetWarningText("");
    return true;
}

bool CSystemMech::isSmallZzSafe()
{
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    pNdtBase->SetWarningText("");
    return true;
}
bool CSystemMech::isSmallFzSafe()
{
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    pNdtBase->SetWarningText("");
    return true;
}

///11.//横臂升降是否安全
bool CSystemMech::isUarmUpSafe()
{
    bool UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //横臂与长台之间大于安全距离
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechArm->getXMin() - gMechLong->getXMax() < NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if(gMechArm->getZ() - gMechLong->getZ() < NDT_SAFE_DIATANCE_100)
        UnSafeZ = true;

    if(UnSafeX && UnSafeZ)
    {
        pNdtBase->SetWarningText("Arm Near to Long Table");
        return false;
    }

    //横臂与圆台之间大于安全距离
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechRound->getXMin() - gMechArm->getXMax()  < NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    UnSafeY  = true;

    if(gMechArm->getZ() - gMechRound->getZ() < NDT_SAFE_DIATANCE_100)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY  && UnSafeZ)
    {
        pNdtBase->SetWarningText("Arm Near to Round Table");
        return false;
    }

    //横臂与球管之间大于安全距离
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechTube->getXMin() - gMechArm->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getZMin() - gMechArm->getZMax() < NDT_SAFE_DIATANCE_200 )
        UnSafeZ = true;

    if( UnSafeX && UnSafeZ)
    {
        pNdtBase->SetWarningText("Arm Near to Tube");
        return false;
    }

    //平板与长台之间大于安全距离
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechPanel->getXMin() - gMechLong->getXMax() < NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if(gMechPanel->getZ() - gMechLong->getZ() < NDT_SAFE_DIATANCE_100)
        UnSafeZ = true;

    if(UnSafeX && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Long Table");
        return false;
    }

    //平板与圆台之间大于安全距离
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechRound->getXMin() - gMechPanel->getXMax()  < NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if( gMechRound->getY() - gMechPanel->getY() < NDT_SAFE_DIATANCE_100 )
        UnSafeY  = true;

    if(gMechPanel->getZ() - gMechRound->getZ() < NDT_SAFE_DIATANCE_100)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY  && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Round Table");
        return false;
    }

    //平板与球管之间大于安全距离
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    if(gMechTube->getXMin() - gMechPanel->getXMax() < NDT_SAFE_DIATANCE_100)
        UnSafeX = true;

    if(gMechTube->getYMin() > gMechPanel->getYMin() - NDT_SAFE_DIATANCE_100 && gMechTube->getYMin() < gMechPanel->getYMax() + NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechTube->getYMax() > gMechPanel->getYMin() - NDT_SAFE_DIATANCE_100 && gMechTube->getYMax() < gMechPanel->getYMax() + NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechTube->getZMin() - gMechPanel->getZMax() < NDT_SAFE_DIATANCE_200)
        UnSafeZ = true;

    if( UnSafeX && UnSafeY && UnSafeZ)
    {
        pNdtBase->SetWarningText("Panel Near to Tube");
        return false;
    }

    pNdtBase->SetWarningText("");

    return true;
}
bool CSystemMech::isUarmDownSafe()
{
    bool UnSafeX = false,UnSafeY = false,UnSafeZ = false;
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    //与长台之间大于安全距离
    if(gMechArm->getXMin() - gMechLong->getXMax() < NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if(gMechArm->getZ() - gMechLong->getZ() < NDT_SAFE_DIATANCE_250)
        UnSafeZ = true;

    if(UnSafeX && UnSafeZ)
    {
        pNdtBase->SetWarningText("Arm Near to Long Table");
        return false;
    }

    //与圆台之间大于安全距离
    UnSafeX = false,UnSafeY = false,UnSafeZ = false;

    if(gMechRound->getXMin() - gMechPanel->getXMax()  < NDT_SAFE_DIATANCE_50)
        UnSafeX = true;

    if( gMechRound->getY() - gMechPanel->getY() < 500 )
        UnSafeY  = true;

    if(gMechPanel->getZ() - gMechRound->getZ() < NDT_SAFE_DIATANCE_200)
        UnSafeZ = true;

    if(UnSafeX && UnSafeY  && UnSafeZ)
    {
        pNdtBase->SetWarningText("Arm Near to Round Table");
        return false;
    }

    //长台不会和平板支撑相撞
    UnSafeX =false,UnSafeY =false,UnSafeZ =false;
    if( gMechPanelBrace->getXMin() - gMechLong->getXMax() <= NDT_SAFE_DIATANCE_100 )
        UnSafeX = true;

    if( gMechPanelBrace->getYMin() - gMechLong->getYMax() <= NDT_SAFE_DIATANCE_100)
        UnSafeY = true;

    if(gMechPanelBrace->getZMin() - gMechLong->getZMax() <= NDT_SAFE_DIATANCE_150 )
        UnSafeZ = true;

    if(UnSafeX && UnSafeY && UnSafeZ )
    {
        pNdtBase->SetWarningText("Long Near to Arm");
        return false;
    }

    pNdtBase->SetWarningText("");
    return true;
}

//所有的安全检测函数
void CSystemMech::CollisionDetect()
{

    //获取CMainBaseNdt，发送命令数据
    CMainBaseNdt10 *pNdtBase = qobject_cast<CMainBaseNdt10*> (RsMgr->g_mainBase);

    ///0.FID,球管升降安全检测
    if(mAutoCheckList.value("isTubeUpSafe",false))
    {

        if(!isTubeUpSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
            DelAutoCheck("isTubeUpSafe");
            qDebug()<<"isTubeUpSafe";
        }
    }

    if(mAutoCheckList.value("isTubeDownSafe",false))
    {
        if(!isTubeDownSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_FID,NDT_MOTOR_STOP);
            DelAutoCheck("isTubeDownSafe");
            qDebug()<<"isTubeDownSafe";
        }
    }

    ///1.SID,球管左右安全检测
    if(mAutoCheckList.value("isTubeLeftSafe",false))
    {

        if(!isTubeLeftSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_SID,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_SID,NDT_MOTOR_STOP);
            DelAutoCheck("isTubeLeftSafe");
            qDebug()<<"isTubeLeftSafe";
        }
    }

    if(mAutoCheckList.value("isTubeRightSafe",false))
    {

        if(!isTubeRightSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_SID,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_SID,NDT_MOTOR_STOP);
            DelAutoCheck("isTubeRightSafe");
            qDebug()<<"isTubeRightSafe";
        }
    }

    ///2.ANG,球管左右安全检测
    if(mAutoCheckList.value("isTubeTurnZzSafe",false))
    {

        if(!isTubeTurnZzSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_ANG,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_ANG,NDT_MOTOR_STOP);
            DelAutoCheck("isTubeTurnZzSafe");
            qDebug()<<"isTubeTurnZzSafe";
        }
    }

    if(mAutoCheckList.value("isTubeTurnFzSafe",false))
    {

        if(!isTubeTurnFzSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_ANG,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_ANG,NDT_MOTOR_STOP);
            DelAutoCheck("isTubeTurnFzSafe");
            qDebug()<<"isTubeTurnFzSafe";
        }
    }

    ///3.CEP,球管前后安全检测
    if(mAutoCheckList.value("isTubeForwordSafe",false))
    {

        if(!isTubeForwordSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_CEP,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_CEP,NDT_MOTOR_STOP);
            DelAutoCheck("isTubeForwordSafe");
            qDebug()<<"isTubeForwordSafe";
        }
    }

    if(mAutoCheckList.value("isTubeBackwordSafe",false))
    {

        if(!isTubeBackwordSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_CEP,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_CEP,NDT_MOTOR_STOP);
            DelAutoCheck("isTubeBackwordSafe");
            qDebug()<<"isTubeBackwordSafe";
        }
    }

    ///4.UID,平板前后安全检测
    if(mAutoCheckList.value("isPanelForwordSafe",false))
    {
        if(!isPanelForwordSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_UID,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_UID,NDT_MOTOR_STOP);
            DelAutoCheck("isPanelForwordSafe");
            qDebug()<<"isPanelForwordSafe";
        }
    }

    if(mAutoCheckList.value("isPanelBackwordSafe",false))
    {
        if(!isPanelBackwordSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_UID,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_UID,NDT_MOTOR_STOP);
            DelAutoCheck("isPanelBackwordSafe");
            qDebug()<<"isPanelBackwordSafe";
        }
    }

    ///5.DTA,平板转动安全检测
    if(mAutoCheckList.value("isPanelTurnVSafe",false))
    {
        if(!isPanelTurnVSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_DTA,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_DTA,NDT_MOTOR_STOP);
            DelAutoCheck("isPanelTurnVSafe");
            qDebug()<<"isPanelTurnVSafe";
        }
    }

    if(mAutoCheckList.value("isPanelTurnHSafe",false))
    {
        if(!isPanelTurnHSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_DTA,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_DTA,NDT_MOTOR_STOP);
            DelAutoCheck("isPanelTurnHSafe");
            qDebug()<<"isPanelTurnHSafe";
        }
    }

    ///6.ROL   大圆台转动安全
    ///7.SRL  小圆台转动安全
    ///8.RMV 大圆台左右移动安全检测
    if(mAutoCheckList.value("isRoundTableLeftSafe",false))
    {
        if(!isRoundTableLeftSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_RMV,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_RMV,NDT_MOTOR_STOP);
            DelAutoCheck("isRoundTableLeftSafe");
            qDebug()<<"isRoundTableLeftSafe";
        }
    }

    if(mAutoCheckList.value("isRoundTableRightSafe",false))
    {

        if(!isRoundTableRightSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_RMV,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_RMV,NDT_MOTOR_STOP);
            DelAutoCheck("isRoundTableRightSafe");
            qDebug()<<"isRoundTableRightSafe";
        }
    }

    ///9.LMV 大圆台左右移动安全检测
    if(mAutoCheckList.value("isLongTableLeftSafe",false))
    {
        if(!isLongTableLeftSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_LMV,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_LMV,NDT_MOTOR_STOP);
            DelAutoCheck("isLongTableLeftSafe");
            qDebug()<<"isLongTableLeftSafe";
        }
    }

    if(mAutoCheckList.value("isLongTableRightSafe",false))
    {
        if(!isLongTableRightSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_LMV,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_LMV,NDT_MOTOR_STOP);
            DelAutoCheck("isLongTableRightSafe");
            qDebug()<<"isLongTableRightSafe";
        }
    }

    ///10.HEI 横臂升降安全检测
    if(mAutoCheckList.value("isUarmUpSafe",false))
    {
        if(!isUarmUpSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);
            DelAutoCheck("isUarmUpSafe");
            qDebug()<<"isUarmUpSafe";
        }
    }

    if(mAutoCheckList.value("isUarmDownSafe",false))
    {
        if(!isUarmDownSafe())
        {
            //pNdtBase->SendKeySingle(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);
            pNdtBase->SendKeyMulti(NDT_KEY_IDX_HEI,NDT_MOTOR_STOP);
            DelAutoCheck("isUarmDownSafe");
            qDebug()<<"isUarmDownSafe";
        }
    }

}


