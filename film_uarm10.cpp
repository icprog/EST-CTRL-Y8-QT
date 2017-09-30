#include "film_uarm10.h"
#include "resource_manager.h"

CFilmUarm10::CFilmUarm10(QWidget *parent) :
    CFilmBase10(parent)
{
    setObjectName("CFilmUarm10");

    m_keyMax = UARM10_KEY_FILM;
    g_keyPtr = &(m_filmUarm10);
}

void CFilmUarm10::SendCmdKey(int mKey)
{
    if(!g_dbsys.utility.mFilmKeyEnable)
        return;

    unsigned short keyBuf[2];
    keyBuf[0] =0;
    keyBuf[1] = mKey;
    g_taskComCtrl->CreateTask(CMD_FUNC_WKEY,keyBuf,2);
}


int CFilmUarm10::m_filmUarm10[SYS_KEY_MAX][2]=
{
    {0x2030,0x0020},//FID增大
    {0x2031,0x0022},//FID减小
    {0x0031,0x0026},//SID减小
    {0x0032,0x0024},//SID增大
    {0x2033,0x0028},//Angle顺时针
    {0x2032,0x002A},//Angle逆时针
    {0x1036,0x0050},//胸片
    {0x1030,0x0052},//床片
    {0x1031,0x0054},//斜线
    {0x1032,0x0040}//滑车移动
};
