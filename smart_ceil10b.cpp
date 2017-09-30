#include "smart_ceil10b.h"

#include "resource_manager.h"

CSmartCeil10b::CSmartCeil10b(QWidget *parent) :
    CSmartBase10(parent)
{
    setObjectName("CSmartCeil10b");

    QFont font;
    font.setPixelSize(SYS_FONT(22));

    mSmartMax = CEIL10b_SMART_MAX;

    pBtnGroup[0]->setText(QApplication::translate("CSmartBase", "Stand 1.8m"));
    pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1 + 1));
    pBtnGroup[0]->setFont(font);
    pBtnGroup[1]->setText(QApplication::translate("CSmartBase", "Stand 1.1m"));
    pBtnGroup[1]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1 + 2));
    pBtnGroup[1]->setFont(font);
    pBtnGroup[2]->setText(QApplication::translate("CSmartBase", "Stand Slash"));
    pBtnGroup[2]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1 + 3));
    pBtnGroup[2]->setFont(font);
    pBtnGroup[3]->setText(QApplication::translate("CSmartBase", "Stand Slash"));
    pBtnGroup[3]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1 + 4));
    pBtnGroup[3]->setFont(font);
    pBtnGroup[4]->setText(QApplication::translate("CSmartBase", "Table"));
    pBtnGroup[4]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1 + 5));
    pBtnGroup[4]->setFont(font);
    pBtnGroup[5]->setText(QApplication::translate("CSmartBase", "Table Slash"));
    pBtnGroup[5]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1 + 6));
    pBtnGroup[5]->setFont(font);
    pBtnGroup[7]->setText(QApplication::translate("CSmartBase", "Free Move"));
    pBtnGroup[7]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1));
    pBtnGroup[7]->setFont(font);

    pBtnGroup[6]->setVisible(false);
    pBtnGroup[8]->setVisible(false);

    m_codeSmart[0] = 0x0050;
    m_codeSmart[1] = 0x0051;
    m_codeSmart[2] = 0x0052;
    m_codeSmart[3] = 0x0053;
    m_codeSmart[4] = 0x0054;
    m_codeSmart[5] = 0x0055;
    m_codeSmart[6] = 0x0058;
    m_codeSmart[7] = 0x0058;
    m_codeSmart[8] = 0x0058;

    m_iSmartRunMax = 6;
    m_iSmartRun[0] = 0;
    m_iSmartRun[1] = 1;
    m_iSmartRun[2] = 2;
    m_iSmartRun[3] = 3;
    m_iSmartRun[4] = 4;
    m_iSmartRun[5] = 5;


}

//快捷状态切换
void CSmartCeil10b::OnStatusChange(int mPos)
{
    if( (mPos < 0) || (mPos > mSmartMax))
        return;

    if(0 == mPos)
        emit RunStatusChange(mPos,(QPushButton*)(0));
    else
        emit RunStatusChange(mPos,pBtnGroup[mPos - 1]);
}

void CSmartCeil10b::OnSmartChange(int mPos)
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
