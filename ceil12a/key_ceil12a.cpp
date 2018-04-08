#include "key_rail12a.h"
#ifdef USE_CEIL_12_A

CKeyCeil12a::CKeyCeil12a(QWidget *parent) :
    CKeyBase12(parent)
{
    //对象名称
    setObjectName("CKeyCeil12a");

    //根据配置文件，创建按钮个数，默认10个按钮(5个动作)
    KeyBtnInit(g_sysDb->value("CKeyCeil12a/KEYMAX","10").toInt());

    //球管转动背景
    frameAngleTube->setStyleSheet(g_skinBase->GetStyleMapStr("BASE12_TUBE_ANGEL_BACK"));

    //按键键码设定
    keyCodeInit();

    //按键位置设定
    keyPositionInit();

    //初始化显示角度
    OnViewDirChange(g_sysDb->g_startAngle);

}

void CKeyCeil12a::keyCodeInit()
{
    //加载按下键码
    pListCodeDown.append(g_sysDb->value("CKeyCeil12a/KEYMAP/0",0x0020).toInt());
    pListCodeDown.append(g_sysDb->value("CKeyCeil12a/KEYMAP/1",0x0022).toInt());
    pListCodeDown.append(g_sysDb->value("CKeyCeil12a/KEYMAP/2",0x0026).toInt());
    pListCodeDown.append(g_sysDb->value("CKeyCeil12a/KEYMAP/3",0x0024).toInt());
    pListCodeDown.append(g_sysDb->value("CKeyCeil12a/KEYMAP/4",0x002a).toInt());
    pListCodeDown.append(g_sysDb->value("CKeyCeil12a/KEYMAP/5",0x0028).toInt());
    pListCodeDown.append(g_sysDb->value("CKeyCeil12a/KEYMAP/6",0x002c).toInt());
    pListCodeDown.append(g_sysDb->value("CKeyCeil12a/KEYMAP/7",0x002e).toInt());
    pListCodeDown.append(g_sysDb->value("CKeyCeil12a/KEYMAP/8",0x0030).toInt());
    pListCodeDown.append(g_sysDb->value("CKeyCeil12a/KEYMAP/9",0x0032).toInt());

    //左右安装方向按键代码切换
    if(g_sysDb->value("utility/mDetectorStandDir",0).toInt() == DirStandRight)
    {
        pListCodeDown.swap(2,3);        //球管左右键码调动
        pListCodeDown.swap(4,5);        //球管转动键码调动
    }

    //调用基类，完成释放后键码的生成
    CKeyBase12::keyCodeInit();

}

void CKeyCeil12a::keyPositionInit()
{

    //按钮在不同角度下的大小
    QList<QRect> tempRect;

    //normal
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL/0"  ,QRect(SYS_HEI(10), SYS_WID( 247),SYS_HEI( 104),SYS_WID(94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL/1"  ,QRect(SYS_HEI(115),SYS_WID( 247),SYS_HEI( 104),SYS_WID(94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL/2"  ,QRect(SYS_HEI(10), SYS_WID( 357),SYS_HEI( 104),SYS_WID(94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL/3"  ,QRect(SYS_HEI(115),SYS_WID( 357),SYS_HEI( 104),SYS_WID(94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL/4"  ,QRect(SYS_HEI(352),SYS_WID( 280),SYS_HEI( 94),SYS_WID( 144))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL/5"  ,QRect(SYS_HEI(258),SYS_WID( 280),SYS_HEI( 94),SYS_WID( 144))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL/6"  ,QRect(SYS_HEI(485),SYS_WID( 247),SYS_HEI( 104),SYS_WID( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL/7"  ,QRect(SYS_HEI(590),SYS_WID( 247),SYS_HEI( 104),SYS_WID( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL/8"  ,QRect(SYS_HEI(485),SYS_WID( 357),SYS_HEI( 104),SYS_WID( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL/9"  ,QRect(SYS_HEI(590),SYS_WID( 357),SYS_HEI( 104),SYS_WID( 94))).toRect());
    pRectKeyBtn.append(tempRect);

    //left
    tempRect.clear();
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT/0"  ,QRect(SYS_WID(246),SYS_HEI( 90),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT/1"  ,QRect(SYS_WID(350),SYS_HEI( 90),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT/2"  ,QRect(SYS_WID(246),SYS_HEI( 184),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT/3"  ,QRect(SYS_WID(350),SYS_HEI( 184),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT/4"  ,QRect(SYS_WID(350),SYS_HEI( 278),SYS_WID( 104),SYS_HEI( 144))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT/5"  ,QRect(SYS_WID(246),SYS_HEI( 278),SYS_WID( 104),SYS_HEI( 144))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT/6"  ,QRect(SYS_WID(246),SYS_HEI( 422),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT/7"  ,QRect(SYS_WID(350),SYS_HEI( 422),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT/8"  ,QRect(SYS_WID(246),SYS_HEI( 516),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT/9"  ,QRect(SYS_WID(350),SYS_HEI( 516),SYS_WID( 104),SYS_HEI( 94))).toRect());
    pRectKeyBtn.append(tempRect);

    //right
    tempRect.clear();
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT/0"  ,QRect(SYS_WID(246),SYS_HEI( 90),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT/1"  ,QRect(SYS_WID(350),SYS_HEI( 90),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT/2"  ,QRect(SYS_WID(246),SYS_HEI( 184),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT/3"  ,QRect(SYS_WID(350),SYS_HEI( 184),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT/4"  ,QRect(SYS_WID(350),SYS_HEI( 278),SYS_WID( 104),SYS_HEI( 144))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT/5"  ,QRect(SYS_WID(246),SYS_HEI( 278),SYS_WID( 104),SYS_HEI( 144))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT/6"  ,QRect(SYS_WID(246),SYS_HEI( 422),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT/7"  ,QRect(SYS_WID(350),SYS_HEI( 422),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT/8"  ,QRect(SYS_WID(246),SYS_HEI( 516),SYS_WID( 104),SYS_HEI( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT/9"  ,QRect(SYS_WID(350),SYS_HEI( 516),SYS_WID( 104),SYS_HEI( 94))).toRect());
    pRectKeyBtn.append(tempRect);

    //reverse
    tempRect.clear();
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE/0"  ,QRect(SYS_HEI(10), SYS_WID( 247),SYS_HEI( 104),SYS_WID(94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE/1"  ,QRect(SYS_HEI(115),SYS_WID( 247),SYS_HEI( 104),SYS_WID(94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE/2"  ,QRect(SYS_HEI(10), SYS_WID( 357),SYS_HEI( 104),SYS_WID(94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE/3"  ,QRect(SYS_HEI(115),SYS_WID( 357),SYS_HEI( 104),SYS_WID(94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE/4"  ,QRect(SYS_HEI(352),SYS_WID( 280),SYS_HEI( 94),SYS_WID( 144))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE/5"  ,QRect(SYS_HEI(258),SYS_WID( 280),SYS_HEI( 94),SYS_WID( 144))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE/6"  ,QRect(SYS_HEI(485),SYS_WID( 247),SYS_HEI( 104),SYS_WID( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE/7"  ,QRect(SYS_HEI(590),SYS_WID( 247),SYS_HEI( 104),SYS_WID( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE/8"  ,QRect(SYS_HEI(485),SYS_WID( 357),SYS_HEI( 104),SYS_WID( 94))).toRect());
    tempRect.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE/9"  ,QRect(SYS_HEI(590),SYS_WID( 357),SYS_HEI( 104),SYS_WID( 94))).toRect());
    pRectKeyBtn.append(tempRect);

    //窗口位置
    pRectKeyWid.append(g_sysDb->value("CKeyCeil12a/VDIR_NORMAL"    ,QRect(SYS_HEI(0),SYS_WID( 0),SYS_HEI( 700 ),SYS_WID( 700 ))).toRect());
    pRectKeyWid.append(g_sysDb->value("CKeyCeil12a/VDIR_LEFT"      ,QRect(SYS_WID(0),SYS_HEI( 0),SYS_WID( 700 ),SYS_HEI( 700 ))).toRect());
    pRectKeyWid.append(g_sysDb->value("CKeyCeil12a/VDIR_RIGHT"     ,QRect(SYS_WID(0),SYS_HEI( 0),SYS_WID( 700 ),SYS_HEI( 700 ))).toRect());
    pRectKeyWid.append(g_sysDb->value("CKeyCeil12a/VDIR_REVERSE"   ,QRect(SYS_HEI(0),SYS_WID( 0),SYS_HEI( 700 ),SYS_WID( 700 ))).toRect());

    //背景球管旋转图标位置
    pRectFrameTube.append(g_sysDb->value("CKeyCeil12a/TUBE/VDIR_NORMAL" ,QRect(SYS_HEI(246),SYS_WID( 253),SYS_HEI( 208),SYS_WID( 194))).toRect());
    pRectFrameTube.append(g_sysDb->value("CKeyCeil12a/TUBE/VDIR_LEFT"   ,QRect(SYS_WID(248),SYS_HEI( 251),SYS_WID( 208),SYS_HEI( 194))).toRect());
    pRectFrameTube.append(g_sysDb->value("CKeyCeil12a/TUBE/VDIR_RIGHT"  ,QRect(SYS_WID(248),SYS_HEI( 251),SYS_WID( 208),SYS_HEI( 194))).toRect());
    pRectFrameTube.append(g_sysDb->value("CKeyCeil12a/TUBE/VDIR_REVERSE",QRect(SYS_HEI(246),SYS_WID( 253),SYS_HEI( 208),SYS_WID( 194))).toRect());

}

#endif
