#include "skin_base12.h"

CSkinBase12::CSkinBase12()
{
    pMapStr.insert("CEIL8_ICON_GEN_UP"      ,"QPushButton{border-image: url(:QRes/com12/icon_generator_up.png);}");
    pMapStr.insert("CEIL8_ICON_GEN_DOWN"    ,"QPushButton{border-image: url(:QRes/com12/icon_generator_down.png);}");
    pMapStr.insert("CEIL8_ICON_MOTION_UP"   ,"QPushButton{border-image: url(:QRes/com12/icon_motion_up.png);}");
    pMapStr.insert("CEIL8_ICON_MOTION_DOWN" ,"QPushButton{border-image: url(:QRes/com12/icon_motion_down.png);}");
    pMapStr.insert("CEIL8_ICON_SYSTEM_UP"   ,"QPushButton{border-image: url(:QRes/com12/icon_system_up.png);}");
    pMapStr.insert("CEIL8_ICON_SYSTEM_DOWN" ,"QPushButton{border-image: url(:QRes/com12/icon_system_down.png);}");

    pMapStr.insert("BASE8_STR_SMART_00" ,"QPushButton{border-image: url(:QRes/com12/icon_smartpos_01_down.png);}");
    pMapStr.insert("BASE8_STR_SMART_01" ,"QPushButton{border-image: url(:QRes/com12/icon_smartpos_01_up.png);}");
    pMapStr.insert("BASE8_STR_SMART_02" ,"QPushButton{border-image: url(:QRes/com12/icon_smartpos_02_down.png);}");
    pMapStr.insert("BASE8_STR_SMART_03" ,"QPushButton{border-image: url(:QRes/com12/icon_smartpos_02_up.png);}");
    pMapStr.insert("BASE8_STR_SMART_04" ,"QPushButton{border-image: url(:QRes/com12/icon_smartpos_03_down.png);}");
    pMapStr.insert("BASE8_STR_SMART_05" ,"QPushButton{border-image: url(:QRes/com12/icon_smartpos_03_up.png);}");

    pMapStr.insert("BASE12_TUBE_ANGEL_BACK" ,"QFrame{border-image: url(:QRes/com12/icon_tube_angle_back.png);}");
    pMapStr.insert("SYS_STR_BACK_FACE_V"    ,"QFrame{border-image: url(:QRes/com12/face-v.png);}");
    pMapStr.insert("SYS_STR_BACK_FACE_L"    ,"QFrame{border-image: url(:QRes/com12/face-l.png);}");
    pMapStr.insert("SYS_STR_BACK_FACE_R"    ,"QFrame{border-image: url(:QRes/com12/face-r.png);}");
    pMapStr.insert("SYS_GEN_BASE"           ,"QFrame {border-image: url(:QRes/com12/generator_base_001.png)}");
    pMapStr.insert("CEIL8_TITLE_LOGO"       ,"QLabel {border-image: url(:QRes/com12/icon_title_logo.png);}");
    pMapStr.insert("BASE8_TITLE_BACK"       ,"QLabel {border-image: url(:QRes/com12/icon_title_back.png);}");

    pMapStr.insert("SYS_NET_REMOTE_DEFAULT" ,"QPushButton{border-image: url(:QRes/com12/icon_remote_default.png);color: rgb(46, 49, 56);}");
    pMapStr.insert("SYS_NET_REMOTE_VIEW"    ,"QPushButton{border-image: url(:QRes/com12/icon_remote_view.png);color: rgb(0, 0, 255);}");
    pMapStr.insert("SYS_NET_REMOTE_CONTROL" ,"QPushButton{border-image: url(:QRes/com12/icon_remote_control.png);color: rgb(0, 255, 0);}");
    pMapStr.insert("SYS_NET_REMOTE_TRY1" ,"QPushButton{border-image: url(:QRes/com12/icon_remote_try_1.png);color: rgb(46, 49, 56);}");
    pMapStr.insert("SYS_NET_REMOTE_TRY2" ,"QPushButton{border-image: url(:QRes/com12/icon_remote_try_2.png);color: rgb(46, 49, 56);}");

    pMapStr.insert("SYS_STR_ICON_EXIT"      ,"QPushButton{border-image: url(:QRes/com12/icon_system_exit.png);}");
    pMapStr.insert("SYS_SIM_OFF"            ,"QPushButton {border-image: url(:QRes/com12/icon_sim_off.png);}");
    pMapStr.insert("SYS_SIM_ON"             ,"QPushButton {border-image: url(:QRes/com12/icon_sim_on.png);}");
    pMapStr.insert("SYS_INFO_BACK_NORMAL"   ,"QLabel {border-image: url(:QRes/com12/sys_info_back.png);color:green;}");
    pMapStr.insert("SYS_INFO_BACK_WARNING"  ,"QLabel {border-image: url(:QRes/com12/sys_info_back.png);color:yellow;}");
    pMapStr.insert("SYS_INFO_BACK_ERROR"    ,"QLabel {border-image: url(:QRes/com12/sys_info_back.png);color:red;}");
    pMapStr.insert("SYS_CURTAIN_OFF"        ,"QPushButton {border-image: url(:QRes/com12/sys_curtain_off.png);}");
    pMapStr.insert("SYS_CURTAIN_ON"         ,"QPushButton {border-image: url(:QRes/com12/sys_curtain_on.png);}");

    pMapStr.insert("ICON_SYSTEM_TECH_ON"   ,"QPushButton{border-image: url(:QRes/com12/icon_system_tech_on.png);}");
    pMapStr.insert("ICON_SYSTEM_TECH_OFF"   ,"QPushButton{border-image: url(:QRes/com12/icon_system_tech_off.png);}");

    pMapInt.insert(SYS_RUN_DOWN_0   ,"QPushButton{border-image: url(:QRes/com12/icon_run_down_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_DOWN_1   ,"QPushButton{border-image: url(:QRes/com12/icon_run_down_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_DOWN_2   ,"QPushButton{border-image: url(:QRes/com12/icon_run_down_2.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_DOWN_3   ,"QPushButton{border-image: url(:QRes/com12/icon_run_down_3.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_UP_0     ,"QPushButton{border-image: url(:QRes/com12/icon_run_up_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_UP_1     ,"QPushButton{border-image: url(:QRes/com12/icon_run_up_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_UP_2     ,"QPushButton{border-image: url(:QRes/com12/icon_run_up_2.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_UP_3     ,"QPushButton{border-image: url(:QRes/com12/icon_run_up_3.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_LEFT_0   ,"QPushButton{border-image: url(:QRes/com12/icon_run_left_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_LEFT_1   ,"QPushButton{border-image: url(:QRes/com12/icon_run_left_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_RIGHT_0  ,"QPushButton{border-image: url(:QRes/com12/icon_run_right_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_RUN_RIGHT_1  ,"QPushButton{border-image: url(:QRes/com12/icon_run_right_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_TURN_LEFT_0  ,"QPushButton{border-image: url(:QRes/com12/icon_turn_left_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_TURN_LEFT_1  ,"QPushButton{border-image: url(:QRes/com12/icon_turn_left_1.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_TURN_RIGHT_0 ,"QPushButton{border-image: url(:QRes/com12/icon_turn_right_0.png);background-repeat:no-repeat;background-position: center;}");
    pMapInt.insert(SYS_TURN_RIGHT_1 ,"QPushButton{border-image: url(:QRes/com12/icon_turn_right_1.png);background-repeat:no-repeat;background-position: center;}");

    pMapStr.insert("SYS_STR_SMART_00"       ,"QPushButton{border-image: url(:QRes/com12/smart_00.png);}");
    pMapInt.insert(SYS_STR_SMART_10  ,"QPushButton{border-image: url(:QRes/com12/smart_00.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_11  ,"QPushButton{border-image: url(:QRes/com12/smart_11.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_12  ,"QPushButton{border-image: url(:QRes/com12/smart_12.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_13  ,"QPushButton{border-image: url(:QRes/com12/smart_13.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_14  ,"QPushButton{border-image: url(:QRes/com12/smart_14.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_15  ,"QPushButton{border-image: url(:QRes/com12/smart_15.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_16  ,"QPushButton{border-image: url(:QRes/com12/smart_16.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_17  ,"QPushButton{border-image: url(:QRes/com12/smart_17.png);text-align: bottom;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_18  ,"QPushButton{border-image: url(:QRes/com12/smart_18.png);text-align: bottom;color: blue;}");


    pMapStr.insert("SYS_INDEX_UP"       ,"border-image: url(:QRes/com/index_Up.png);");
    pMapStr.insert("SYS_INDEX_DOWN"     ,"border-image: url(:QRes/com/index_Down.png);");

    pMapStr.insert("SYS_TECH_UP"    ,"QPushButton{border-image: url(:QRes/com8/btn_tech_01.png);}");
    pMapStr.insert("SYS_TECH_DOWN"  ,"QPushButton{border-image: url(:QRes/com8/btn_tech_02.png);}");

    //通用按钮
    pMapStr.insert("SYS_STR_BTN_001"  ,"QPushButton{border-image: url(:QRes/com8/btn_01_01.png);}");
    pMapStr.insert("SYS_STR_BTN_002"  ,"QPushButton{border-image: url(:QRes/com8/btn_01_02.png);}");
    pMapStr.insert("SYS_STR_BTN_003"  ,"QPushButton{border-image: url(:QRes/com8/btn_01_03.png);}");
    pMapStr.insert("SYS_STR_BTN_004"  ,"QPushButton{border-image: url(:QRes/com8/btn_01_04.png);}");

    //    pMapInt.insert(SYS_TURN_LEFT_2    ,"QPushButton{border-image: url(:QRes/com8/icon_turn_left_2.png);background-repeat:no-repeat;background-position: center;}");
    //    pMapInt.insert(SYS_TURN_RIGHT_2    ,"QPushButton{border-image: url(:QRes/com8/icon_turn_right_2.png);background-repeat:no-repeat;background-position: center;}");
    //    pMapInt.insert(SYS_RUN_LEFT_2    ,"QPushButton{border-image: url(:QRes/com8/icon_run_left_2.png);background-repeat:no-repeat;background-position: center;}");
    //    pMapInt.insert(SYS_RUN_RIGHT_2    ,"QPushButton{border-image: url(:QRes/com8/icon_run_right_2.png);background-repeat:no-repeat;background-position: center;}");


    pMapInt.insert(SYS_STR_SMART_01  ,"QPushButton{border-image: url(:QRes/com8/smart_01.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_02  ,"QPushButton{border-image: url(:QRes/com8/smart_02.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_03  ,"QPushButton{border-image: url(:QRes/com8/smart_03.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_04  ,"QPushButton{border-image: url(:QRes/com8/smart_04.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_05  ,"QPushButton{border-image: url(:QRes/com8/smart_05.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_06  ,"QPushButton{border-image: url(:QRes/com8/smart_06.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_07  ,"QPushButton{border-image: url(:QRes/com8/smart_07.png);text-align: right;color: blue;}");
    pMapInt.insert(SYS_STR_SMART_08  ,"QPushButton{border-image: url(:QRes/com8/smart_08.png);text-align: right;color: blue;}");

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

