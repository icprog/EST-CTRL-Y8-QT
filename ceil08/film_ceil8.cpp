#include "film_ceil8.h"
#include "resource_manager.h"
#define CEIL8_KEY_FILM          ( 10 )  /*物理薄膜按键数量*/
CFilmCeil8::CFilmCeil8(QWidget *parent) :
    CFilmBase8(parent)
{
    setObjectName("CFilmCeil8");

    //当立柱右侧安装时，部分按键键码需要反向
    if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
    {

        m_filmCeil8[2][1] = 0x0024;
        m_filmCeil8[3][1] = 0x0026;
        m_filmCeil8[4][1] = 0x002A;
        m_filmCeil8[5][1] = 0x0028;

    }

    m_keyMax = CEIL8_KEY_FILM;
    g_keyPtr = &(m_filmCeil8);
}


int CFilmCeil8::m_filmCeil8[SYS_KEY_MAX][2]=
{
    {0x2030,0x0020},//FID增大
    {0x2031,0x0022},//FID减小
    {0x0032,0x0024},//SID增大
    {0x0031,0x0026},//SID减小
    {0x2033,0x0028},//Angle顺时针
    {0x2032,0x002A},//Angle逆时针
    {0x1036,0x0050},//胸片
    {0x1030,0x0052},//床片
    {0x1031,0x0054},//斜线
    {0x1032,0x0040} //滑车移动
};
