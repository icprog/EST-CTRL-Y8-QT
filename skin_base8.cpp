#include "skin_base8.h"

CSkinBase8::CSkinBase8()
{
    pMapStr.insert("CEIL8_ICON_GEN_UP"      ,"QPushButton{border-image: url(:QRes/com8/icon_generator_up.png);}");
    pMapStr.insert("CEIL8_ICON_GEN_DOWN"    ,"QPushButton{border-image: url(:QRes/com8/icon_generator_down.png);}");
    pMapStr.insert("CEIL8_ICON_MOTION_UP"   ,"QPushButton{border-image: url(:QRes/com8/icon_motion_up.png);}");
    pMapStr.insert("CEIL8_ICON_MOTION_DOWN" ,"QPushButton{border-image: url(:QRes/com8/icon_motion_down.png);}");
    pMapStr.insert("CEIL8_ICON_SYSTEM_UP"   ,"QPushButton{border-image: url(:QRes/com8/icon_system_up.png);}");
    pMapStr.insert("CEIL8_ICON_SYSTEM_DOWN" ,"QPushButton{border-image: url(:QRes/com8/icon_system_down.png);}");

    pMapStr.insert("SYS_INDEX_UP"       ,"border-image: url(:QRes/com/index_Up.png);");
    pMapStr.insert("SYS_INDEX_DOWN"     ,"border-image: url(:QRes/com/index_Down.png);");
    pMapStr.insert("SYS_STR_ICON_EXIT"  ,"QPushButton{border-image: url(:QRes/com8/icon_system_exit.png);}");
    pMapStr.insert("SYS_STR_BACK_FACE"  ,"QFrame{border-image: url(:QRes/com8/face.png);}");

    pMapStr.insert("CEIL8_TITLE_LOGO"  ,"QLabel {border-image: url(:QRes/com8/icon_title_logo.png);}");

    pMapStr.insert("SYS_TECH_UP"    ,"QPushButton{border-image: url(:QRes/com8/btn_tech_01.png);}");
    pMapStr.insert("SYS_TECH_DOWN"  ,"QPushButton{border-image: url(:QRes/com8/btn_tech_02.png);}");

    //通用按钮
    pMapStr.insert("SYS_STR_BTN_001"  ,"QPushButton{border-image: url(:QRes/com8/btn_01_01.png);}");
    pMapStr.insert("SYS_STR_BTN_002"  ,"QPushButton{border-image: url(:QRes/com8/btn_01_02.png);}");
    pMapStr.insert("SYS_STR_BTN_003"  ,"QPushButton{border-image: url(:QRes/com8/btn_01_03.png);}");
    pMapStr.insert("SYS_STR_BTN_004"  ,"QPushButton{border-image: url(:QRes/com8/btn_01_04.png);}");

    pMapStr.insert("SYS_SIM_OFF"        ,"QPushButton {border-image: url(:QRes/com8/icon_sim_off.png);}");
    pMapStr.insert("BASE8_TITLE_BACK"  ,"QLabel {border-image: url(:QRes/com8/icon_sim_off.png);}");

    pMapStr.insert("BASE8_STR_SMART_00" ,"QPushButton{border-image: url(:QRes/com8/icon_smartpos_01_down.png);}");
    pMapStr.insert("BASE8_STR_SMART_01" ,"QPushButton{border-image: url(:QRes/com8/icon_smartpos_01_up.png);}");
    pMapStr.insert("BASE8_STR_SMART_02" ,"QPushButton{border-image: url(:QRes/com8/icon_smartpos_02_down.png);}");
    pMapStr.insert("BASE8_STR_SMART_03" ,"QPushButton{border-image: url(:QRes/com8/icon_smartpos_02_up.png);}");
    pMapStr.insert("BASE8_STR_SMART_04" ,"QPushButton{border-image: url(:QRes/com8/icon_smartpos_03_down.png);}");
    pMapStr.insert("BASE8_STR_SMART_05" ,"QPushButton{border-image: url(:QRes/com8/icon_smartpos_03_up.png);}");

    pMapInt.insert(SYS_TURN_LEFT_0    ,"QPushButton{border-image: url(:QRes/com8/icon_turn_left_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_TURN_LEFT_1    ,"QPushButton{border-image: url(:QRes/com8/icon_turn_left_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_TURN_LEFT_2    ,"QPushButton{border-image: url(:QRes/com8/icon_turn_left_2.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_TURN_RIGHT_0    ,"QPushButton{border-image: url(:QRes/com8/icon_turn_right_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_TURN_RIGHT_1    ,"QPushButton{border-image: url(:QRes/com8/icon_turn_right_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_TURN_RIGHT_2    ,"QPushButton{border-image: url(:QRes/com8/icon_turn_right_2.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_LEFT_0    ,"QPushButton{border-image: url(:QRes/com8/icon_run_left_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_LEFT_1    ,"QPushButton{border-image: url(:QRes/com8/icon_run_left_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_LEFT_2    ,"QPushButton{border-image: url(:QRes/com8/icon_run_left_2.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_RIGHT_0    ,"QPushButton{border-image: url(:QRes/com8/icon_run_right_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_RIGHT_1    ,"QPushButton{border-image: url(:QRes/com8/icon_run_right_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_RIGHT_2    ,"QPushButton{border-image: url(:QRes/com8/icon_run_right_2.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_UP_0    ,"QPushButton{border-image: url(:QRes/com8/icon_run_up_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_UP_1    ,"QPushButton{border-image: url(:QRes/com8/icon_run_up_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_UP_2    ,"QPushButton{border-image: url(:QRes/com8/icon_run_up_2.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_UP_3    ,"QPushButton{border-image: url(:QRes/com8/icon_run_up_3.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_DOWN_0    ,"QPushButton{border-image: url(:QRes/com8/icon_run_down_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_DOWN_1    ,"QPushButton{border-image: url(:QRes/com8/icon_run_down_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_DOWN_2    ,"QPushButton{border-image: url(:QRes/com8/icon_run_down_2.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_DOWN_3    ,"QPushButton{border-image: url(:QRes/com8/icon_run_down_3.png);background-repeat:no-repeat;background-position: center;}");


    pMapInt.insert(SYS_STR_SMART_01  ,"QPushButton{border-image: url(:QRes/com8/smart_01.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_02  ,"QPushButton{border-image: url(:QRes/com8/smart_02.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_03  ,"QPushButton{border-image: url(:QRes/com8/smart_03.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_04  ,"QPushButton{border-image: url(:QRes/com8/smart_04.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_05  ,"QPushButton{border-image: url(:QRes/com8/smart_05.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_06  ,"QPushButton{border-image: url(:QRes/com8/smart_06.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_07  ,"QPushButton{border-image: url(:QRes/com8/smart_07.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_08  ,"QPushButton{border-image: url(:QRes/com8/smart_08.png);text-align: right;color: blue;}");

    pMapInt.insert(SYS_STR_SMART_10  ,"QPushButton{border-image: url(:QRes/com8/smart_10.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_11  ,"QPushButton{border-image: url(:QRes/com8/smart_11.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_12  ,"QPushButton{border-image: url(:QRes/com8/smart_12.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_13  ,"QPushButton{border-image: url(:QRes/com8/smart_13.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_14  ,"QPushButton{border-image: url(:QRes/com8/smart_14.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_15  ,"QPushButton{border-image: url(:QRes/com8/smart_15.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_16  ,"QPushButton{border-image: url(:QRes/com8/smart_16.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_17  ,"QPushButton{border-image: url(:QRes/com8/smart_17.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_18  ,"QPushButton{border-image: url(:QRes/com8/smart_18.png);text-align: bottom;color: blue;}");

    pMapInt.insert(SYS_STR_SMART_20  ,"background-image: url(:QRes/com8/smart_00.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_21  ,"background-image: url(:QRes/com8/smart_01.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_22  ,"background-image: url(:QRes/com8/smart_02.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_23  ,"background-image: url(:QRes/com8/smart_03.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_24  ,"background-image: url(:QRes/com8/smart_04.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_25  ,"background-image: url(:QRes/com8/smart_05.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_26  ,"background-image: url(:QRes/com8/smart_06.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_27  ,"background-image: url(:QRes/com8/smart_07.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");
    pMapInt.insert(SYS_STR_SMART_28  ,"background-image: url(:QRes/com8/smart_08.png);background-repeat:no-repeat;background-position: left center;text-align: right;color: blue;");

}

