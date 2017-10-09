#include "smart_ceil10a.h"

#include "resource_manager.h"

CSmartCeil10a::CSmartCeil10a(QWidget *parent) :
    CSmartBase10(parent)
{

    setObjectName("CSmartCeil10a");

    QFont font;
    font.setPixelSize(SYS_FONT(22));

    mSmartMax = CEIL10a_SMART_MAX;

    pBtnGroup[0]->setText(QApplication::translate("CSmartBase", "Free Move"));
    pBtnGroup[1]->setText(QApplication::translate("CSmartBase", "Stand 1.8m"));
    pBtnGroup[2]->setText(QApplication::translate("CSmartBase", "Stand 1.1m"));
    pBtnGroup[3]->setText(QApplication::translate("CSmartBase", "Stand Slash"));
    pBtnGroup[4]->setText(QApplication::translate("CSmartBase", "Stand Slash"));
    pBtnGroup[5]->setText(QApplication::translate("CSmartBase", "Stand Position"));
    pBtnGroup[6]->setText(QApplication::translate("CSmartBase", "Table"));
    pBtnGroup[7]->setText(QApplication::translate("CSmartBase", "Table Slash"));
    pBtnGroup[8]->setText(QApplication::translate("CSmartBase", "Table Slash"));

    QRect rectTemp = pBtnGroup[mSmartMax - 1]->geometry();

    for(int mIdx = mSmartMax - 1; mIdx > 0 ; mIdx--)
    {
        pBtnGroup[mIdx]->setGeometry(pBtnGroup[mIdx - 1]->geometry());
        pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1 + mIdx));
        pBtnGroup[mIdx]->setFont(font);
    }

    pBtnGroup[0]->setGeometry(rectTemp);
    pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1));

    m_codeSmart[0] = 0x0058;
    m_codeSmart[1] = 0x0050;
    m_codeSmart[2] = 0x0051;
    m_codeSmart[3] = 0x0052;
    m_codeSmart[4] = 0x0053;
    m_codeSmart[5] = 0x0054;
    m_codeSmart[6] = 0x0055;
    m_codeSmart[7] = 0x0056;
    m_codeSmart[8] = 0x0057;

    m_iSmartRunMax = 8;
    m_iSmartRun[0] = 1;
    m_iSmartRun[1] = 2;
    m_iSmartRun[2] = 3;
    m_iSmartRun[3] = 4;
    m_iSmartRun[4] = 5;
    m_iSmartRun[5] = 6;
    m_iSmartRun[6] = 7;
    m_iSmartRun[7] = 8;

}

void CSmartCeil10a::OnSmartChange(int mPos)
{
    switch(mPos)
    {
    case SMART_POS_00:
        CSmartBase::SendCmdKey(m_codeSmart[SMART_POS_00]);
        m_iSmartChannel = SMART_NULL;
        //g_taskComCtrl->DataLogStop();
        break;
    case SMART_POS_01:
        //g_taskComCtrl->DataLogStart();
        CSmartBase::SendCmdKey(m_codeSmart[SMART_POS_01]);
        m_iSmartChannel = SMART_STAND;
        break;
    case SMART_POS_02:
        //g_taskComCtrl->DataLogStart();
        CSmartBase::SendCmdKey(m_codeSmart[SMART_POS_02]);
        m_iSmartChannel = SMART_STAND;
        break;
    case SMART_POS_03:
        //g_taskComCtrl->DataLogStart();
        CSmartBase::SendCmdKey(m_codeSmart[SMART_POS_03]);
        m_iSmartChannel = SMART_STAND_SLASH;
        break;
    case SMART_POS_04:
        //g_taskComCtrl->DataLogStart();
        CSmartBase::SendCmdKey(m_codeSmart[SMART_POS_04]);
        m_iSmartChannel = SMART_STAND_SLASH;
        break;
    case SMART_POS_05:
        //g_taskComCtrl->DataLogStart();
        CSmartBase::SendCmdKey(m_codeSmart[SMART_POS_05]);
        m_iSmartChannel = SMART_STAND_TABLE;
        break;
    case SMART_POS_06:
        //g_taskComCtrl->DataLogStart();
        CSmartBase::SendCmdKey(m_codeSmart[SMART_POS_06]);
        m_iSmartChannel = SMART_TABLE;
        break;
    case SMART_POS_07:
        //g_taskComCtrl->DataLogStart();
        CSmartBase::SendCmdKey(m_codeSmart[SMART_POS_07]);
        m_iSmartChannel = SMART_TABLE_SLASH;
        break;
    case SMART_POS_08:
        //g_taskComCtrl->DataLogStart();
        CSmartBase::SendCmdKey(m_codeSmart[SMART_POS_08]);
        m_iSmartChannel = SMART_TABLE_SLASH;
        break;
    }

}
