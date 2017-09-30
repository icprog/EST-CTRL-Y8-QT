#include "skin_base10.h"
//#include "resource_manager.h"


CSkinBase10::CSkinBase10()
{
    pMapStr.insert("SYS_MEASURE_BEH","QFrame {border-image: url(:QRes/com10/measure_beh.png);}");
    pMapStr.insert("SYS_STR_ICON_EXIT","QPushButton{border-image: url(:QRes/com10/icon_system_exit.png);}");
    pMapStr.insert("SYS_STR_BACK_FACE"  ,"QFrame{border-image: url(:QRes/com10/face.png);}");

    pMapStr.insert("SYS_TECH_UP"    ,"QPushButton{border-image: url(:QRes/com10/btn_tech_01.png);}");
    pMapStr.insert("SYS_TECH_DOWN"  ,"QPushButton{border-image: url(:QRes/com10/btn_tech_02.png);}");

    pMapStr.insert("SYS_STR_BTN_001"  ,"QPushButton{border-image: url(:QRes/com10/btn_01_01.png);}");
    pMapStr.insert("SYS_STR_BTN_002"  ,"QPushButton{border-image: url(:QRes/com10/btn_01_01.png);}");
    pMapStr.insert("SYS_STR_BTN_003"  ,"QPushButton{border-image: url(:QRes/com10/btn_01_01.png);}");
    pMapStr.insert("SYS_STR_BTN_004"  ,"QPushButton{border-image: url(:QRes/com10/btn_01_01.png);}");

    pMapStr.insert("SYS_SIM_OFF"    ,"QPushButton {border-image: url(:QRes/com10/icon_sim_off.png);}");
    pMapStr.insert("BASE10_MOTION_LIFT"        ,"QFrame {border-image: url(:QRes/com10/motion_lift.png);background: transparent;}");
    pMapStr.insert("BASE10_MOTION_CEIL"        ,"QLabel {border-image: url(:QRes/com10/motion_ceilling.png);}");

     //g_skinBase->GetStyleMapStr("SYS_LEFT_GEN_UP")

    pMapStr.insert("SYS_LEFT_GEN_UP"        ,"QPushButton{border-image: url(:QRes/com10/btn-left-gen-up.png);}");
    pMapStr.insert("SYS_LEFT_GEN_DOWN"        ,"QPushButton{border-image: url(:QRes/com10/btn-left-gen-down.png);}");
    pMapStr.insert("SYS_LEFT_CFG_UP"        ,"QPushButton{border-image: url(:QRes/com10/btn-left-config-up.png);}");
    pMapStr.insert("SYS_LEFT_CFG_DOWN"        ,"QPushButton{border-image: url(:QRes/com10/btn-left-config-down.png);}");
    pMapStr.insert("SYS_RIGHT_GEN_UP"        ,"QPushButton{border-image: url(:QRes/com10/btn-right-gen-up.png);}");
    pMapStr.insert("SYS_RIGHT_GEN_DOWN"        ,"QPushButton{border-image: url(:QRes/com10/btn-right-gen-down.png);}");
    pMapStr.insert("SYS_RIGHT_CFG_UP"        ,"QPushButton{border-image: url(:QRes/com10/btn-right-config-up.png);}");
    pMapStr.insert("SYS_RIGHT_CFG_DOWN"        ,"QPushButton{border-image: url(:QRes/com10/btn-right-config-down.png);}");

    pMapInt.insert(SYS_STR_SMART_01    ,"QPushButton{border-image: url(:QRes/com10/smart_01.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_02    ,"QPushButton{border-image: url(:QRes/com10/smart_02.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_03    ,"QPushButton{border-image: url(:QRes/com10/smart_03.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_04    ,"QPushButton{border-image: url(:QRes/com10/smart_04.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_05    ,"QPushButton{border-image: url(:QRes/com10/smart_05.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_06    ,"QPushButton{border-image: url(:QRes/com10/smart_06.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_07    ,"QPushButton{border-image: url(:QRes/com10/smart_07.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_08    ,"QPushButton{border-image: url(:QRes/com10/smart_08.png);text-align: right;color: blue;}");

    pMapInt.insert(SYS_STR_SMART_10    ,"QPushButton{border-image: url(:QRes/com10/smart_10.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_11    ,"QPushButton{border-image: url(:QRes/com10/smart_11.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_12    ,"QPushButton{border-image: url(:QRes/com10/smart_12.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_13    ,"QPushButton{border-image: url(:QRes/com10/smart_13.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_14    ,"QPushButton{border-image: url(:QRes/com10/smart_14.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_15    ,"QPushButton{border-image: url(:QRes/com10/smart_15.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_16    ,"QPushButton{border-image: url(:QRes/com10/smart_16.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_17    ,"QPushButton{border-image: url(:QRes/com10/smart_17.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_18    ,"QPushButton{border-image: url(:QRes/com10/smart_18.png);text-align: bottom;color: blue;}");

    pMapInt.insert(SYS_STR_SMART_20    ,"background-image: url(:QRes/com10/smart_00.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_21    ,"background-image: url(:QRes/com10/smart_01.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_22    ,"background-image: url(:QRes/com10/smart_02.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_23    ,"background-image: url(:QRes/com10/smart_03.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_24    ,"background-image: url(:QRes/com10/smart_04.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_25    ,"background-image: url(:QRes/com10/smart_05.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_26    ,"background-image: url(:QRes/com10/smart_06.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_27    ,"background-image: url(:QRes/com10/smart_07.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_28    ,"background-image: url(:QRes/com10/smart_08.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");


    QString mStr;
    for(int mIdx = 0 ;mIdx < MENU10_BTN_ICON_MAX * MENU10_BTN_KEY_STEP ; mIdx++)
    {
        mStr.sprintf("QPushButton {border-image: url(:QRes/com10/btn-key-%03d.png);}",mIdx);
        pMapInt.insert(mIdx + MENU10_BTN_BASE,mStr);
    }
}
