#include "skin_rail12a.h"

#ifdef USE_CEIL_12_A

CSkinCeil12a::CSkinCeil12a()
{
    pMapStr.insert("SYS_MEASURE_SID"    ,"QFrame {border-image: url(:QRes/8010/png00/measure_sid.png);}");
    pMapStr.insert("SYS_MEASURE_DTH"    ,"QFrame {border-image: url(:QRes/8010/png00/measure_dth.png);}");
    pMapStr.insert("SYS_MEASURE_FID"    ,"QFrame {border-image: url(:QRes/8010/png00/measure_fid.png);}");
    pMapStr.insert("SYS_MEASURE_BEH"    ,"QFrame {border-image: url(:QRes/8010/png00/measure_beh.png);}");
    pMapStr.insert("SYS_MEASURE_ANG"    ,"QFrame {border-image: url(:QRes/8010/png00/measure_ang.png);}");

    pMapStr.insert("RAIL8_MOVIE_BACK"    ,"QFrame {border-image: url(:QRes/8010/png00/motion_back.png);}");
    pMapStr.insert("RAIL8_MOVIE_STAND"    ,"QLabel {border-image: url(:QRes/8010/png00/motion_stand.png);}");
    pMapStr.insert("RAIL8_MOVIE_DET"    ,"QFrame {border-image: url(:QRes/8010/png00/motion_detecter.png);}");
    pMapStr.insert("RAIL8_MOVIE_TUBE"    ,"QFrame {border-image: url(:QRes/8010/png00/motion_tube.png);background:transparent}");
    pMapStr.insert("RAIL8_MOVIE_TABLE"    ,"QLabel {border-image: url(:QRes/8010/png00/motion_table.png);}");
    pMapStr.insert("RAIL8_MOVIE_BUCKY"    ,"QFrame {border-image: url(:QRes/8010/png00/motion_tabledet.png);}");
    pMapStr.insert("RAIL8_MOVIE_ACCORD"    ,"QFrame {border-image: url(:QRes/8010/png00/motion_accordion.png);background:transparent}");

    pMapStr.insert("MAIN_BACK_NORMAL"   ,"QFrame{ border-image: url(:QRes/8010/png00/background-v.png);}");
    pMapStr.insert("MAIN_BACK_LEFT"   ,"QFrame{ border-image: url(:QRes/8010/png00/background-l.png);}");
    pMapStr.insert("MAIN_BACK_RIGHT"   ,"QFrame{ border-image: url(:QRes/8010/png00/background-r.png);}");
    pMapStr.insert("MAIN_BACK_R180"   ,"QFrame{ border-image: url(:QRes/8010/png00/background-n.png);}");

    QString mStr;
    //按键图标
    for(int mIdx = 0 ;mIdx < 20 ; mIdx++)
    {
        mStr.sprintf("QPushButton {border-image: url(:QRes/com12/btn-key-%03d.png);}",mIdx);
        pMapInt.insert(mIdx + KEY_ICON_BASE,mStr);
    }

}


#endif  //USE_RAIL_12_A
