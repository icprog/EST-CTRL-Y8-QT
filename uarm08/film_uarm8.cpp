#include "film_uarm8.h"
#include "resource_manager.h"

#define UARM8_KEY_FILM              ( 10 )  /*物理薄膜按键数量*/

CFilmUarm8::CFilmUarm8(QWidget *parent) :
    CFilmBase8(parent)
{
    setObjectName("CFilmUarm8");

    m_keyMax = UARM8_KEY_FILM;
    g_keyPtr = &(m_filmUarm8);
}

void CFilmUarm8::SendCmdKey(int mKey)
{
    if(g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_00)
        SendCmdKey00(mKey);

    if(g_dbsys.utility.mCommProtocol == COMM_PROTOCOL_01)
        SendCmdKey01(mKey);
}

void CFilmUarm8::SendCmdKey01(int mKey)
{
    if(!g_dbsys.utility.mFilmKeyEnable)
        return;

    switch(mKey)
    {
    case 0x0050:
        m_keyTag = SMART_POS_01;
        mKey = 0x0058;
        timerFilmLong->start();
        break;
    case 0x0052:
        m_keyTag = SMART_POS_05;
        mKey = 0x0058;
        timerFilmLong->start();
        break;
    case 0x0054:
        mKey = 0x0057;
        break;
    case 0x0051:
    case 0x0053:
    case 0x0055:
        timerFilmLong->stop();
        return;
    default:
        break;
    }

    CFilmBase::SendCmdKey(mKey);
}

void CFilmUarm8::SendCmdKey00(int mKey)
{
    if(!g_dbsys.utility.mFilmKeyEnable)
        return;

    switch(mKey)
    {
    case 0x0050:
        m_keyTag = SMART_POS_01;
        timerFilmLong->start();
        break;
    case 0x0052:
        m_keyTag = SMART_POS_05;
        timerFilmLong->start();
        break;
    case 0x0054:
        mKey = 0x0055;
        break;
    case 0x0051:
    case 0x0053:
    case 0x0055:
        timerFilmLong->stop();
        return;
    default:
        break;
    }

    CFilmBase::SendCmdKey(mKey);
}

int CFilmUarm8::m_filmUarm8[SYS_KEY_MAX][2]=
{
    {0x2030,0x0020},//HEI增大
    {0x2031,0x0022},//HEI减小
    {0x2032,0x002A},//Angle逆时针
    {0x2033,0x0028},//Angle顺时针
    {0x1036,0x0050},//胸片
    {0x1030,0x0052},//床片
    {0x1031,0x0054},//斜线
    {0x1032,0x0040},//滑车移动
    {0x0031,0x0026},//SID减小
    {0x0032,0x0024} //SID增大
};
