#include "smart_base10.h"
#include "resource_manager.h"

CSmartBase10::CSmartBase10(QWidget *parent)
    :CSmartBase(parent)
{
    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(70,90,130,150));
    setPalette(pal);

    m_iSmartState = SMART_STATE_FREE;

    OnViewDirChange(VIEW_DIR_NORMAL);
}

void CSmartBase10::OnSelfRunControl()
{

    if( m_iSmartState == SMART_STATE_CMD_WAIT)      //等待命令到位
    {
        if(SmartCmdWait())                          //执行完毕
        {
            m_iSmartState = SMART_STATE_SLASH_WAIT;
            m_iTimerCounter = 0;                    //重新计数
        }
        return;
    }

    if(m_iSmartState == SMART_STATE_SLASH_WAIT)
    {
        if(m_iTimerCounter < g_systemDb->m_SelfRunInterval) //判断时间间隔是否到达
            return;
        else
            m_iSmartState = SMART_STATE_FREE;
    }

    if(  m_iSmartState == SMART_STATE_FREE)     //发送快捷命令
    {
        OnSmartChange(m_iSmartRun[m_iSmartIndex]);

        m_iSmartIndex ++;
        if(m_iSmartIndex >= m_iSmartRunMax)
            m_iSmartIndex = 0;

        m_iSmartState = SMART_STATE_CMD_WAIT;
    }

}

int CSmartBase10::SmartCmdWait()
{
    if(g_systemDb->g_dbMachine.CurrentData[16] == 1 || g_systemDb->g_dbMachine.CurrentData[17] == 1 || g_systemDb->g_dbMachine.CurrentData[18] == 1 )
        return true;    //一键为已经到位，还需要等待斜线到位

    return false;
}

void CSmartBase10::OnViewDirChange(int mDir)
{

    if(mDir == VIEW_DIR_NORMAL)
    {
        resize(SYS_HEI(380),SYS_WID(330));

        for(int mIdx = 0 ; mIdx < 3 ; mIdx++)
        {
            for(int mCtr = 0 ; mCtr < 3 ; mCtr++)
            {
                pBtnGroup[mIdx * 3 + mCtr]->setGeometry(SYS_HEI(5 + mCtr * 125),SYS_WID(5 + mIdx * 110),SYS_HEI(120),SYS_WID(100));
            }
        }
        return;
    }

    if(mDir == VIEW_DIR_LEFT || mDir == VIEW_DIR_RIGHT)
    {
        resize(SYS_WID(380),SYS_HEI(330));

        for(int mIdx = 0 ; mIdx < 3 ; mIdx++)
        {
            for(int mCtr = 0 ; mCtr < 3 ; mCtr++)
            {
                pBtnGroup[mIdx * 3 + mCtr]->setGeometry(SYS_WID(5 + mCtr * 125),SYS_HEI(5 + mIdx * 110),SYS_WID(120),SYS_HEI(100));
            }
        }
        return;
    }

}
