#include "skin_uarm8.h"

CSkinUarm8::CSkinUarm8()
{
    pMapStr.insert("SYS_MEASURE_ANG"    ,"QFrame {border-image: url(:QRes/8021/png00/measure_ang.png);}");
    pMapStr.insert("SYS_MEASURE_DTA"    ,"QFrame {border-image: url(:QRes/8021/png00/measure_dta.png);}");
    pMapStr.insert("SYS_MEASURE_FID"    ,"QFrame {border-image: url(:QRes/8021/png00/measure_fid.png);}");
    pMapStr.insert("SYS_MEASURE_HEI"    ,"QFrame {border-image: url(:QRes/8021/png00/measure_hei.png);}");

    pMapStr.insert("UARM8_MOVIE_STAND"  ,"QFrame {border-image: url(:QRes/8021/png00/movie_stand.png);}");
    pMapStr.insert("UARM8_MOVIE_UARM"   ,"QLabel {border-image: url(:QRes/8021/png00/movie_uarm.png);background : transparent}");
    pMapStr.insert("UARM8_MOVIE_DET"    ,"QFrame {border-image: url(:QRes/8021/png00/movie_detecter.png);background:transparent}");
    pMapStr.insert("UARM8_MOVIE_TUBE"   ,"QFrame {border-image: url(:QRes/8021/png00/movie_tube.png);background:transparent}");
}
