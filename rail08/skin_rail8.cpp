#include "skin_rail8.h"

CSkinRail8::CSkinRail8()
{
    pMapStr.insert("SYS_MEASURE_SID"    ,"QFrame {border-image: url(:QRes/8011/png00/measure_sid.png);}");
    pMapStr.insert("SYS_MEASURE_DTP"    ,"QFrame {border-image: url(:QRes/8011/png00/measure_dtp.png);}");
    pMapStr.insert("SYS_MEASURE_FID"    ,"QFrame {border-image: url(:QRes/8011/png00/measure_fid.png);}");
    pMapStr.insert("SYS_MEASURE_BEH"    ,"QFrame {border-image: url(:QRes/8011/png00/measure_beh.png);}");

    pMapStr.insert("RAIL8_MOVIE_BACK"    ,"QFrame {border-image: url(:QRes/8011/png00/motion_back.png);}");
    pMapStr.insert("RAIL8_MOVIE_STAND"    ,"QLabel {border-image: url(:QRes/8011/png00/motion_stand.png);}");
    pMapStr.insert("RAIL8_MOVIE_DET"    ,"QFrame {border-image: url(:QRes/8011/png00/motion_detecter.png);}");
    pMapStr.insert("RAIL8_MOVIE_TUBE"    ,"QFrame {border-image: url(:QRes/8011/png00/motion_tube.png);background:transparent}");
    pMapStr.insert("RAIL8_MOVIE_TABLE"    ,"QLabel {border-image: url(:QRes/8011/png00/motion_table.png);}");
    pMapStr.insert("RAIL8_MOVIE_BUCKY"    ,"QFrame {border-image: url(:QRes/8011/png00/motion_tabledet.png);}");
    pMapStr.insert("RAIL8_MOVIE_ACCORD"    ,"QFrame {border-image: url(:QRes/8011/png00/motion_accordion.png);background:transparent}");
}
