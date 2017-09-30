#include "film_ceil10b.h"
#include "resource_manager.h"

CFilmCeil10b::CFilmCeil10b(QWidget *parent) :
    CFilmBase10(parent)
{
    setObjectName("CFilmCeil10b");

    //当立柱右侧安装时，部分按键键码需要反向
    if(g_dbsys.utility.mDetectorStandDir == DETECTOR_STAND_RIGHT)
    {
        m_filmCeil10b[2][1] = 0x0026;
        m_filmCeil10b[3][1] = 0x0024;
        m_filmCeil10b[4][1] = 0x002a;
        m_filmCeil10b[5][1] = 0x0028;
        m_filmCeil10b[11][1] = 0x002a;
        m_filmCeil10b[12][1] = 0x0028;
    }

    m_keyMax = CEIL10_B_KEY_FILM;
    g_keyPtr = &(m_filmCeil10b);
}

void CFilmCeil10b::SendCmdKey(int mKey)
{
    if(!g_dbsys.utility.mFilmKeyEnable)
        return;

    switch(mKey)
    {
    case 0x005a:
        m_keyTag = 0x0050;
        CFilmBase::SendCmdKey(0x0058);
        timerFilmLong->start();
        break;
    case 0x005c:
        m_keyTag = 0x0051;
        CFilmBase::SendCmdKey(0x0058);
        timerFilmLong->start();
        break;
    case 0x005e:
        m_keyTag = 0x0054;
        CFilmBase::SendCmdKey(0x0058);
        timerFilmLong->start();
        break;
    case 0x005b:
    case 0x005d:
    case 0x005f:
        timerFilmLong->stop();
        return;
    default:
        break;
    }

    CFilmBase::SendCmdKey(mKey);
}

int CFilmCeil10b::m_filmCeil10b[SYS_KEY_MAX][2]=
{
    {0x0031,0x0020},//FID增大
    {0x0032,0x0022},//FID减小
    {0x2031,0x0024},//SID增大
    {0x2030,0x0026},//SID减小
    {0x0033,0x0028},//ANG增大
    {0x1012,0x002A},//ANG减小
    {0x2033,0x0034},//CEP增大
    {0x2032,0x0036},//CEP减小
    {0x1032,0x005a},//胸片1.8
    {0x1031,0x005c},//胸片1.1
    {0x1030,0x005e},//床片
    {0x4035,0x0028},//ANG增大
    {0x4037,0x002A}//ANG减小
};
