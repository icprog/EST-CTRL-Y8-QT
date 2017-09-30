#include "skin_base.h"

QMap<int , QString> CSkinBase::pMapInt;
QMap<QString , QString> CSkinBase::pMapStr;

CSkinBase::CSkinBase()
{
    //系统通用部分加载
    pMapStr.insert("BASE_STR_USB"       ,"QLabel{border-image: url(:QRes/com/usb.png);}");
    pMapStr.insert("BASE_STR_DEBUG"     ,"QLabel{border-image: url(:QRes/com/picture_info_debug.png);background-color: red;}");
    pMapStr.insert("BASE_STR_NORMAL"    ,"QLabel{border-image: url(:QRes/com/picture_info_normal.png);background-color: green;}");
    pMapStr.insert("BASE_STR_SETTING"   ,"QLabel{border-image: url(:QRes/com/picture_info_setting.png);background-color: yellow;}");

    pMapStr.insert("SYS_STR_CRITICAL"   ,"QFrame {border-image: url(:QRes/com/Info_Critical.png);}");
    pMapStr.insert("SYS_STR_INFO"       ,"QFrame {border-image: url(:QRes/com/Info_Information.png);}");
    pMapStr.insert("SYS_STR_WARNING"    ,"QFrame {border-image: url(:QRes/com/Info_Warning.png);}");
    pMapStr.insert("SYS_STR_ERROR"      ,"QFrame {border-image: url(:QRes/com/Info_Error.png);}");
    pMapStr.insert("SYS_STR_QUESTION"   ,"QFrame {border-image: url(:QRes/com/Info_Question.png);}");

    //通用数据显示图标
    pMapStr.insert("SYS_MEASURE_ANG"    ,"QFrame {border-image: url(:QRes/com/measure_ang.png);}");
    pMapStr.insert("SYS_MEASURE_DTA"    ,"QFrame {border-image: url(:QRes/com/measure_dta.png);}");
    pMapStr.insert("SYS_MEASURE_DTH"    ,"QFrame {border-image: url(:QRes/com/measure_dth.png);}");
    pMapStr.insert("SYS_MEASURE_FID"    ,"QFrame {border-image: url(:QRes/com/measure_fid.png);}");
    pMapStr.insert("SYS_MEASURE_SID"    ,"QFrame {border-image: url(:QRes/com/measure_sid.png);}");

    pMapStr.insert("SYS_STR_SMART_00"   ,"QPushButton{border-image: url(:QRes/com/smart_00.png);text-align: right;color: blue;}");
    pMapStr.insert("BASE_STR_PASSWORD"  ,"QPushButton{border-image: url(:QRes/com/pas.png);}");
    pMapStr.insert("BASE_STR_GENERAL"   ,"QPushButton{border-image: url(:QRes/com/general_setting.png);}");
    pMapStr.insert("SYS_FSMALL_01"      ,"QPushButton{border-image: url(:QRes/com/focus_small_00.png);}");
    pMapStr.insert("SYS_FSMALL_02"      ,"QPushButton{border-image: url(:QRes/com/focus_small_01.png);}");
    pMapStr.insert("SYS_FLARGE_01"      ,"QPushButton{border-image: url(:QRes/com/focus_large_00.png);}");
    pMapStr.insert("SYS_FLARGE_02"      ,"QPushButton{border-image: url(:QRes/com/focus_large_01.png);}");
    pMapStr.insert("SYS_SIM_ON"         ,"QPushButton {border-image: url(:QRes/com/icon_sim_on.png);}");

    //通用发生器图标
    pMapStr.insert("SYS_GEN_BASE"       ,"QFrame {border-image: url(:QRes/com/generator_base_001.png)}");
    pMapStr.insert("SYS_STR_GEN_KV"     ,"QPushButton {border-image: url(:QRes/com/picture_gen_kv_01.png);background-repeat:no-repeat;text-align: center;}");
    pMapStr.insert("SYS_STR_GEN_MAS"    ,"QPushButton {border-image: url(:QRes/com/picture_gen_mas_01.png);background-repeat:no-repeat;text-align: center;}");
    pMapStr.insert("SYS_STR_GEN_MA"     ,"QPushButton {border-image: url(:QRes/com/picture_gen_ma_01.png);background-repeat:no-repeat;text-align: center;}");
    pMapStr.insert("SYS_STR_GEN_MS"     ,"QPushButton {border-image: url(:QRes/com/picture_gen_ms_01.png);background-repeat:no-repeat;text-align: center;}");
    pMapStr.insert("SYS_INDEX_PRE"      ,"QPushButton{border-image: url(:QRes/com/index_Pre.png);}");
    pMapStr.insert("SYS_INDEX_NEXT"     ,"QPushButton{border-image: url(:QRes/com/index_Next.png);}");
    pMapStr.insert("SYS_GEN_RAD_01"     ,"QPushButton{border-image: url(:QRes/com/rad_01.png);}");
    pMapStr.insert("SYS_GEN_RAD_02"     ,"QPushButton{border-image: url(:QRes/com/rad_02.png);}");

    //通用屏幕旋转图标
    pMapStr.insert("SYS_SCREEN_LEFT_01"    ,"QPushButton{border-image: url(:QRes/com/bt_screen_left_01.png);}");
    pMapStr.insert("SYS_SCREEN_LEFT_02"    ,"QPushButton{border-image: url(:QRes/com/bt_screen_left_02.png);}");
    pMapStr.insert("SYS_SCREEN_RIGHT_01"   ,"QPushButton{border-image: url(:QRes/com/bt_screen_right_01.png);}");
    pMapStr.insert("SYS_SCREEN_RIGHT_02"   ,"QPushButton{border-image: url(:QRes/com/bt_screen_right_02.png);}");

    pMapInt.insert(SYS_AEC_00    ,"QPushButton{border-image: url(:QRes/com/btn_aec_01_0.png);}");
    pMapInt.insert(SYS_AEC_01    ,"QPushButton{border-image: url(:QRes/com/btn_aec_01_1.png);}");
    pMapInt.insert(SYS_AEC_10    ,"QPushButton{border-image: url(:QRes/com/btn_aec_02_0.png);}");
    pMapInt.insert(SYS_AEC_11    ,"QPushButton{border-image: url(:QRes/com/btn_aec_02_1.png);}");
    pMapInt.insert(SYS_AEC_20    ,"QPushButton{border-image: url(:QRes/com/btn_aec_03_0.png);}");
    pMapInt.insert(SYS_AEC_21    ,"QPushButton{border-image: url(:QRes/com/btn_aec_03_1.png);}");
    pMapInt.insert(SYS_AEC_30    ,"QPushButton{border-image: url(:QRes/com/btn_aec_04_0.png);}");
    pMapInt.insert(SYS_AEC_31    ,"QPushButton{border-image: url(:QRes/com/btn_aec_04_1.png);}");
    pMapInt.insert(SYS_AEC_40    ,"QPushButton{border-image: url(:QRes/com/btn_aec_05_0.png);}");
    pMapInt.insert(SYS_AEC_41    ,"QPushButton{border-image: url(:QRes/com/btn_aec_05_1.png);}");
    pMapInt.insert(SYS_AEC_50    ,"QPushButton{border-image: url(:QRes/com/btn_aec_06_0.png);}");
    pMapInt.insert(SYS_AEC_51    ,"QPushButton{border-image: url(:QRes/com/btn_aec_06_1.png);}");
    pMapInt.insert(SYS_AEC_60    ,"QPushButton{border-image: url(:QRes/com/btn_aec_07_0.png);}");
    pMapInt.insert(SYS_AEC_61    ,"QPushButton{border-image: url(:QRes/com/btn_aec_07_1.png);}");
}
//修改资源的存储位置
void CSkinBase::ConfigResource(QString nPath)
{
    QString mBuf;

    QMap<int , QString>::const_iterator pInt = pMapInt.constBegin();
    while (pInt != pMapInt.constEnd()) {
        mBuf =  pInt.value();
        mBuf.replace(":QRes/",nPath);
        pMapInt.insert(pInt.key(),mBuf);
        //fprintf(stderr,"%d=%s\n\r",pInt.key(),pInt.value().toStdString().data());
        ++pInt;
    }

    QMap<QString , QString>::const_iterator pStr = pMapStr.constBegin();
    while (pStr != pMapStr.constEnd()) {
        mBuf =  pStr.value();
        mBuf.replace(":QRes/",nPath);
        pMapStr.insert(pStr.key(),mBuf);
        //fprintf(stderr,"%s=%s\n\r",pStr.key().toStdString().data(),pStr.value().toStdString().data());
        ++pStr;
    }
}
QString CSkinBase::GetStyleMapStr(int mStrIdx)
{

    return pMapInt.value(mStrIdx,NULL);

}

QString CSkinBase::GetStyleMapStr(QString mStr)
{    

    return pMapStr.value(mStr,NULL);

}

