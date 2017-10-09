#include "skin_ceil8.h"

CSkinCeil8::CSkinCeil8()
{
    pMapStr.insert("CEIL8_MOVIE_BACK"      ,"QFrame {border-image: url(:QRes/8001/png00/movie_back_ground.png);}");
    pMapStr.insert("CEIL8_MOVIE_LIFT"      ,"QFrame {border-image: url(:QRes/8001/png00/movie_lift.png);background:transparent}");
    pMapStr.insert("CEIL8_MOVIE_DET"       ,"QFrame {border-image: url(:QRes/8001/png00/movie_detecter.png);background:transparent}");
    pMapStr.insert("CEIL8_MOVIE_TUBE"      ,"QFrame {border-image: url(:QRes/8001/png00/movie_tube.png);background:transparent}");
    pMapStr.insert("CEIL8_MOVIE_CEIL"      ,"QLabel {border-image: url(:QRes/8001/png00/movie_scroll.png);}");
    pMapStr.insert("CEIL8_MOVIE_STAND_ARM" ,"QLabel {border-image: url(:QRes/8001/png00/movie_stand_arm.png);}");
}
