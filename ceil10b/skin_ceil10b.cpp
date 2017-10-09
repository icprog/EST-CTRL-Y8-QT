#include "skin_ceil10b.h"

CSkinCeil10b::CSkinCeil10b()
{
    pMapStr.insert("CEIL10b_MOTION_BACK"        ,"QFrame {border-image: url(:QRes/8040/png00/motion_back.png);}");
    pMapStr.insert("CEIL10b_MOTION_STAND_DET"   ,"QLabel {border-image: url(:QRes/8040/png00/motion_standdet.png);background: transparent}");
    pMapStr.insert("CEIL10b_MOTION_STAND_ARM"   ,"QFrame {border-image: url(:QRes/8040/png00/motion_standarm.png);}");
    pMapStr.insert("CEIL10b_MOTION_TUBE"        ,"QFrame {border-image: url(:QRes/8040/png00/motion_tube.png);background: transparent;}");

    //修改天轨一个方向的按键为立柱上下
    QString mStr;
    for(int mIdx = 12 ;mIdx < 24 ; mIdx++)
    {
        mStr.sprintf("QPushButton {border-image: url(:QRes/8040/png00/btn-key-%03d.png);}",mIdx);
        pMapInt.insert(mIdx + MENU10_BTN_BASE,mStr);
    }

    //修改最底部的按钮为1.8米，1.1米，卧位
    for(int mIdx = 54 ;mIdx < 66 ; mIdx++)
    {
        mStr.sprintf("QPushButton {border-image: url(:QRes/8040/png00/btn-key-%03d.png);}",mIdx);
        pMapInt.insert(mIdx + MENU10_BTN_BASE,mStr);
    }
}
