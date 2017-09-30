#include "film_base12.h"
#include "resource_manager.h"

CFilmBase12::CFilmBase12(QWidget *parent) :
    CFilmBase(parent)
{

    connect(timerFilmLong,SIGNAL(timeout()),this,SLOT(OnTimerFilmLong()));

}

void CFilmBase12::SendCmdKey(int mKey)
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

void CFilmBase12::OnTimerFilmLong()
{
    emit SmartChange(m_keyTag);
    SetKeySound();
}

//扫描键码并显示
void CFilmBase12::filmKeyDisplay(unsigned short mKeyPhisic)
{

    if(mKeyPhisic == 0xff)
        return;

    //jinsongyang 20160229 add led indicate for keys with led
    if(mKeyPhisic == 0x1036)
    {
        g_systemDb->g_dbMachine.CurrentData[16] = 2;
        g_systemDb->g_dbMachine.CurrentData[17] = 0;
        g_systemDb->g_dbMachine.CurrentData[18] = 0;
    }

    if(mKeyPhisic == 0x1030)
    {
        g_systemDb->g_dbMachine.CurrentData[16] = 0;
        g_systemDb->g_dbMachine.CurrentData[17] = 2;
        g_systemDb->g_dbMachine.CurrentData[18] = 0;
    }

    if(mKeyPhisic == 0x1031)
    {
        g_systemDb->g_dbMachine.CurrentData[16] = 0;
        g_systemDb->g_dbMachine.CurrentData[17] = 0;
        g_systemDb->g_dbMachine.CurrentData[18] = 2;
    }


    mStrBuf.setNum(mKeyPhisic,16);
    lbCurrentCode->setText(mStrBuf);

    if(mKeyPhisic == 0xf0)
    {
        nKey = keylast + 1;

        mStrBuf.setNum(nKey,16);
        lbFunctionUp->setText(mStrBuf);

        g_systemDb->g_dbMachine.CurrentData[16] = 0;
        g_systemDb->g_dbMachine.CurrentData[17] = 0;
        g_systemDb->g_dbMachine.CurrentData[18] = 0;

    }else
    {
        for(int i = 0; i < m_keyMax ; i++)
        {
            if(mKeyPhisic == (*g_keyPtr)[i][0])
            {
                keylast = (*g_keyPtr)[i][1];

                if(nKey == keylast)
                    return;

                nKey = (*g_keyPtr)[i][1];

                mStrBuf.setNum(nKey,16);
                lbFunctionDown->setText(mStrBuf);

                break;
            }
        }
    }
}
