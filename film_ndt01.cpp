#include "film_ndt01.h"
#include "resource_manager.h"
#include <fcntl.h>
#include <sys/ioctl.h>

#define NDT01_A_KEY_FILM 13

CFilmNdt01::CFilmNdt01(QWidget *parent) :
    CFilmBase10(parent)
{
    setObjectName("CFilmNdt01");

    m_keyMax = NDT01_A_KEY_FILM;
    g_keyPtr = &(m_filmNdt);

}
void CFilmNdt01::SendCmdKey(int mKey)
{
    if(!g_dbsys.utility.mFilmKeyEnable)
        return;

    qDebug()<<"KEY:"<<mKey<<" Down!";

}
//薄膜按键LED灯控制
void CFilmNdt01::filmLed(int LedStat)
{

    if(!g_taskComKey)
        return;

    switch(LedStat)
    {
    case FILM_LED_STAND:
        m_bufLed[0] &= 0x0000;
        m_bufLed[1] = 0x0010;
        g_taskComKey->CreateTask(COMM_TX_LED,m_bufLed,5);
        break;
    case FILM_LED_TABLE:
        m_bufLed[0] = 0x0001;
        m_bufLed[1] &= 0x0000;
        g_taskComKey->CreateTask(COMM_TX_LED,m_bufLed,5);
        break;
    case FILM_LED_TUBE:
        m_bufLed[0] = 0x0000;
        m_bufLed[1] = 0x4000;
        g_taskComKey->CreateTask(COMM_TX_LED,m_bufLed,5);
        break;
    case FILM_LED_ALL_FLASH:
        return;
    case FILM_LED_ALL_ON:
        return;
    case FILM_LED_ALL_OFF:
        return;
    default:
        return;
    }

}

int CFilmNdt01::m_filmNdt[SYS_KEY_MAX][2]=
{
    {0x1032,0},//0
    {0x1031,1},//1
    {0x1030,2}, //2
    {0x2030,3},//3
    {0x4037,4},//4
    {0x2031,5},//5
    {0x4035,6},//6
    {0x2032,7},//7
    {0x0032,8},//8
    {0x2033,9},//9
    {0x0031,10}//10
};
/*
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
*/
