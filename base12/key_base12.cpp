#include "key_base12.h"
#include "resource_manager.h"

CKeyBase12::CKeyBase12(QWidget *parent) :
    CKeyBase(parent)
{

    frameAngleTube = new QFrame(this);
    frameAngleTube->setGeometry(SYS_WID(262),SYS_HEI( 263),SYS_WID( 208),SYS_HEI( 194));
    frameAngleTube->setStyleSheet(g_skinBase->GetStyleMapStr("BASE12_TUBE_ANGEL_BACK"));

    if(g_mainCfg->value("ShowPartBackColor",false).toInt() == false)
    {
        setStyleSheet("background:transparent");
    }else
    {
        //设置背景色
        QPalette pal = palette();
        pal.setColor(QPalette::Background, QColor(208,100,245));
        setPalette(pal);
    }

}
void CKeyBase12::KeyBtnInit()
{
    //创建所有的按钮，设为不可见
    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        pBtnGroup[mIdx] = new CButtonStable(this);
        pBtnGroup[mIdx]->setVisible(false);
    }
}
void CKeyBase12::KeyBtnSlotInit()
{
    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        pBtnGroup[mIdx]->setVisible(true);
        pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(m_iIconList[2*mIdx]));

        if(g_dbsys.utility.mScreenKeyEnable)
        {
            connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(motionKeyPressed()));
            connect(pBtnGroup[mIdx],SIGNAL(released()),this,SLOT(motionKeyReleased()));
        }
    }

}

void CKeyBase12::motionKeyPressed()
{
    //关闭自运行
    g_systemDb->SetAutoRun(false);

    int keyDown = -1;

    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        if(pBtnGroup[mIdx] == sender())
        {
            keyDown = mIdx;
            break;
        }
    }

    if(keyDown == -1 )
        return;

    SendCmdKey(keyBtnDown[keyDown]);

    pBtnGroup[keyDown]->setStyleSheet(g_skinBase->GetStyleMapStr(m_iIconList[2*keyDown + 1]));

    emit softWareKeyDown(keyBtnDown[keyDown]);

    emit ViewChange(VIEW_MOTION);

}
void CKeyBase12::motionKeyReleased()
{

    int keyUp = -1;

    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        if(pBtnGroup[mIdx] == sender())
        {
            keyUp = mIdx;
            break;
        }
    }

    if(keyUp == -1 )
        return;

    SendCmdKey(keyBtnUp[keyUp]);        //执行按键
    //切换图标
    pBtnGroup[keyUp]->setStyleSheet(g_skinBase->GetStyleMapStr(m_iIconList[2*keyUp]));

    emit softWareKeyUp(keyBtnUp[keyUp]);//通知其他部件
}

void CKeyBase12::OnViewDirChange(int viewPoint)
{

    switch(viewPoint)
    {
    case VIEW_DIR_R180:
        break;
    case VIEW_DIR_NORMAL:
        pBtnGroup[0]->setGeometry(SYS_WID(26), SYS_HEI( 244),SYS_WID(108),SYS_HEI(108));
        pBtnGroup[1]->setGeometry(SYS_WID(134),SYS_HEI( 249),SYS_WID( 108),SYS_HEI( 108));
        pBtnGroup[2]->setGeometry(SYS_WID(28), SYS_HEI( 354),SYS_WID( 108),SYS_HEI(  92));
        pBtnGroup[3]->setGeometry(SYS_WID(133),SYS_HEI( 355),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[4]->setGeometry(SYS_WID(363),SYS_HEI( 290),SYS_WID( 90),SYS_HEI( 143));
        pBtnGroup[5]->setGeometry(SYS_WID(272),SYS_HEI( 290),SYS_WID( 90),SYS_HEI( 143));
        pBtnGroup[6]->setGeometry(SYS_WID(495),SYS_HEI( 265),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[7]->setGeometry(SYS_WID(513),SYS_HEI( 354),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[8]->setGeometry(SYS_WID(589),SYS_HEI( 263),SYS_WID( 108),SYS_HEI( 108));
        pBtnGroup[9]->setGeometry(SYS_WID(602),SYS_HEI( 350),SYS_WID( 108),SYS_HEI( 108));
        frameAngleTube->setGeometry(SYS_WID(262),SYS_HEI( 263),SYS_WID( 208),SYS_HEI( 194));
        break;
    case VIEW_DIR_LEFT: //向左90度
        pBtnGroup[0]->setGeometry(SYS_WID(252),SYS_HEI( 101),SYS_WID(108),SYS_HEI(108));
        pBtnGroup[1]->setGeometry(SYS_WID(361),SYS_HEI( 105),SYS_WID( 108),SYS_HEI(  108));
        pBtnGroup[2]->setGeometry(SYS_WID(254),SYS_HEI( 203),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[3]->setGeometry(SYS_WID(361),SYS_HEI( 203),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[4]->setGeometry(SYS_WID(363),SYS_HEI( 300),SYS_WID( 90),SYS_HEI( 143));
        pBtnGroup[5]->setGeometry(SYS_WID(273),SYS_HEI( 300),SYS_WID( 90),SYS_HEI( 143));
        pBtnGroup[6]->setGeometry(SYS_WID(251),SYS_HEI( 446),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[7]->setGeometry(SYS_WID(361),SYS_HEI( 446),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[8]->setGeometry(SYS_WID(254),SYS_HEI( 525),SYS_WID( 108),SYS_HEI( 108));
        pBtnGroup[9]->setGeometry(SYS_WID(359),SYS_HEI( 524),SYS_WID( 108),SYS_HEI( 108));
        frameAngleTube->setGeometry(SYS_WID(257),SYS_HEI( 272),SYS_WID( 208),SYS_HEI( 194));
        break;
    case VIEW_DIR_RIGHT://向左90度
        pBtnGroup[0]->setGeometry(SYS_WID(252),SYS_HEI( 101),SYS_WID(108),SYS_HEI(108));
        pBtnGroup[1]->setGeometry(SYS_WID(361),SYS_HEI( 105),SYS_WID( 108),SYS_HEI(  108));
        pBtnGroup[2]->setGeometry(SYS_WID(254),SYS_HEI( 203),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[3]->setGeometry(SYS_WID(361),SYS_HEI( 203),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[4]->setGeometry(SYS_WID(363),SYS_HEI( 300),SYS_WID( 90),SYS_HEI( 143));
        pBtnGroup[5]->setGeometry(SYS_WID(273),SYS_HEI( 300),SYS_WID( 90),SYS_HEI( 143));
        pBtnGroup[6]->setGeometry(SYS_WID(251),SYS_HEI( 446),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[7]->setGeometry(SYS_WID(361),SYS_HEI( 446),SYS_WID( 108),SYS_HEI( 92));
        pBtnGroup[8]->setGeometry(SYS_WID(254),SYS_HEI( 525),SYS_WID( 108),SYS_HEI( 108));
        pBtnGroup[9]->setGeometry(SYS_WID(359),SYS_HEI( 524),SYS_WID( 108),SYS_HEI( 108));
        frameAngleTube->setGeometry(SYS_WID(257),SYS_HEI( 272),SYS_WID( 208),SYS_HEI( 194));
        break;
    default:
        break;
    }
}
