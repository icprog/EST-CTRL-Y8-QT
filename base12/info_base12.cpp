#include "info_base12.h"
#include "resource_manager.h"

CInfoBase12::CInfoBase12(QWidget *parent) :
    CInfoBase(parent)
{

    setObjectName("CInfoBase12");

    lbMsgIcon->setVisible(false);

    QFont font;
    font.setPixelSize(SYS_FONT(32));
    lbMsgInfo->setFont(font);

    lbMsgInfo->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INFO_BACK_NORMAL"));

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        setStyleSheet("background-color:rgb(22,200,22)");
    }

    OnInfoMsgCtrl(INFO_CTRL_ADD,MSG_NORMAL);

    OnViewDirChange(g_systemDb->g_startAngle);
}

void CInfoBase12::OnInfoFresh()
{

    CInfoBase::OnInfoFresh();

    if(m_iRunStatus != g_systemDb->g_dbMachine.StateData[2])
    {
        m_iRunStatus = g_systemDb->g_dbMachine.StateData[2];
        emit RunStatusChange(m_iRunStatus);
    }
}
void CInfoBase12::InfoDisplay()
{

    if(m_iMsgLevel[m_iLevelPtr] != 0)               //当前优先级有待显示信息
    {

        int mLevel = m_iMsgPicture[m_iMsgDispInx];  //获取当前待显示信息的等级

        while(mLevel != m_iLevelPtr)                //判断当前的等级是否需要显示
        {
            m_iMsgDispInx++;
            if(m_iMsgDispInx >= m_iMsgNum )
            {
                m_iMsgDispInx = 0;
                return;
            }

            mLevel = m_iMsgPicture[m_iMsgDispInx];
        }

        if(INFO_PIC_ERROR == m_iMsgPicture[m_iMsgDispInx])
        {
            lbMsgInfo->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INFO_BACK_ERROR"));
            setVisible(true);
        }

        if(INFO_PIC_WARNING == m_iMsgPicture[m_iMsgDispInx])
        {
            lbMsgInfo->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INFO_BACK_WARNING"));
            setVisible(true);
        }

        if(INFO_PIC_INFO == m_iMsgPicture[m_iMsgDispInx])
        {
            lbMsgInfo->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INFO_BACK_NORMAL"));
            setVisible(false);
        }

        lbMsgInfo->setText(m_iMsgInfo[m_iMsgDispInx]);

        //根据文字长度，调整文本框长度,调整文本框位置
        //首先计算文本框宽度
        //根据宽度，计算新的位置，使文本框在动画下面，居中
        int textWidth,startXPos;
        /*
        textWidth = 36 * m_iMsgInfo[m_iMsgDispInx].length() + 80 ;
        startXPos = SYS_WID((500 - textWidth ) / 2);
        lbMsgInfo->setGeometry(startXPos, SYS_HEI(214), SYS_WID(textWidth), SYS_HEI(72));
            */
        switch(g_systemDb->g_startAngle)
        {
        case VIEW_DIR_NORMAL:
          //  resize(SYS_HEI(500),SYS_WID(500));
            textWidth = 36 * m_iMsgInfo[m_iMsgDispInx].length() + 80 ;
            startXPos = SYS_HEI((500 - textWidth ) / 2);
            lbMsgInfo->setGeometry(startXPos, SYS_WID(214), SYS_HEI(textWidth), SYS_WID(72));
            break;
        case VIEW_DIR_LEFT:
          //  resize(SYS_WID(500),SYS_HEI(500));
            textWidth = 36 * m_iMsgInfo[m_iMsgDispInx].length() + 80 ;
            startXPos = SYS_WID((500 - textWidth ) / 2);
            lbMsgInfo->setGeometry(startXPos, SYS_HEI(214), SYS_WID(textWidth), SYS_HEI(72));
            break;
        case VIEW_DIR_RIGHT:
          //  resize(SYS_WID(500),SYS_HEI(500));
            textWidth = 36 * m_iMsgInfo[m_iMsgDispInx].length() + 80 ;
            startXPos = SYS_WID((500 - textWidth ) / 2);
            lbMsgInfo->setGeometry(startXPos, SYS_HEI(214), SYS_WID(textWidth), SYS_HEI(72));
            break;
        case VIEW_DIR_R180:
            break;
        default:
            break;

        }

        m_iMsgDispInx++;

        if(m_iMsgDispInx >= m_iMsgNum)
            m_iMsgDispInx = 0;

        return;
    }

}

void CInfoBase12::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        resize(SYS_HEI(500),SYS_WID(500));
        break;
    case VIEW_DIR_LEFT:
        resize(SYS_WID(500),SYS_HEI(500));
        break;
    case VIEW_DIR_RIGHT:
        resize(SYS_WID(500),SYS_HEI(500));
        break;
    case VIEW_DIR_R180:
        break;
    default:
        break;

    }
}

void CInfoBase12::InfoMonitor()
{
    CInfoBase::InfoMonitor();
}

void CInfoBase12::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
    timerInfoFresh->start();
}
void CInfoBase12::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
    //timerInfoFresh->stop();
}
