#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_B

#include "info_rail08b.h"
#include "resource_manager.h"

CInfoRail08b::CInfoRail08b(QWidget *parent) :
    CInfoBase8(parent)
{
    setObjectName("CInfoRail08b");

    lbMsgIcon->setVisible(false);

    QFont font;
    font.setPixelSize(SYS_FONT(28));
    lbMsgInfo->setFont(font);

    lbMsgInfo->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_INFO_BACK_NORMAL"));

    OnViewDirChange(g_systemDb->g_startAngle);
}
void CInfoRail08b::OnViewDirChange(int sAngle)
{

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        setGeometry(g_mainCfg->value("CInfoRail08b/VIEW_DIR_NORMAL/Geometry",QRect(0,0,SYS_WID(400),SYS_HEI(400))).toRect());
        break;
    case VIEW_DIR_LEFT:
        setGeometry(g_mainCfg->value("CInfoRail08b/VIEW_DIR_LEFT/Geometry",QRect(0,0,SYS_HEI(400),SYS_WID(400))).toRect());
        break;
    case VIEW_DIR_RIGHT:
        setGeometry(g_mainCfg->value("CInfoRail08b/VIEW_DIR_RIGHT/Geometry",QRect(0,0,SYS_HEI(400),SYS_WID(400))).toRect());
        break;
    case VIEW_DIR_R180:
        setGeometry(g_mainCfg->value("CInfoRail08b/VIEW_DIR_R180/Geometry",QRect(0,0,SYS_WID(400),SYS_HEI(400))).toRect());
        break;
    default:
        setGeometry(g_mainCfg->value("CInfoRail08b/VIEW_DIR_R180/Geometry",QRect(0,0,SYS_WID(400),SYS_HEI(400))).toRect());
        break;
    }
}

void CInfoRail08b::InfoDisplay()
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

        switch(g_systemDb->g_startAngle)
        {
        case VIEW_DIR_NORMAL:
            textWidth = 36 * m_iMsgInfo[m_iMsgDispInx].length() + 80 ;
            startXPos = SYS_WID((400 - textWidth ) / 2);
            lbMsgInfo->setGeometry(startXPos, SYS_HEI(166), SYS_WID(textWidth), SYS_HEI(68));
            break;
        case VIEW_DIR_LEFT:
            textWidth = 36 * m_iMsgInfo[m_iMsgDispInx].length() + 80 ;
            startXPos = SYS_HEI((400 - textWidth ) / 2);
            lbMsgInfo->setGeometry(startXPos, SYS_WID(166), SYS_HEI(textWidth), SYS_WID(68));
            break;
        case VIEW_DIR_RIGHT:
            textWidth = 36 * m_iMsgInfo[m_iMsgDispInx].length() + 80 ;
            startXPos = SYS_HEI((400 - textWidth ) / 2);
            lbMsgInfo->setGeometry(startXPos, SYS_WID(166), SYS_HEI(textWidth), SYS_WID(68));
            break;
        case VIEW_DIR_R180:
            textWidth = 36 * m_iMsgInfo[m_iMsgDispInx].length() + 80 ;
            startXPos = SYS_WID((400 - textWidth ) / 2);
            lbMsgInfo->setGeometry(startXPos, SYS_HEI(166), SYS_WID(textWidth), SYS_HEI(68));
            break;
        default:
            textWidth = 36 * m_iMsgInfo[m_iMsgDispInx].length() + 80 ;
            startXPos = SYS_WID((400 - textWidth ) / 2);
            lbMsgInfo->setGeometry(startXPos, SYS_HEI(166), SYS_WID(textWidth), SYS_HEI(68));
            break;

        }

        m_iMsgDispInx++;

        if(m_iMsgDispInx >= m_iMsgNum)
            m_iMsgDispInx = 0;

        return;
    }

}

void CInfoRail08b::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}
#endif //USE_RAIL_08_B
