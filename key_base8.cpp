#include "key_base8.h"
#include "resource_manager.h"

CKeyBase8::CKeyBase8(QWidget *parent) :
    CKeyBase(parent)
{

    QPalette pal = palette();
    pal.setColor(QPalette::Background, QColor(208,235,245));
    setPalette(pal);

}
void CKeyBase8::KeyBtnInit()
{
    //创建所有的按钮，设为不可见
    for(int mIdx = 0 ; mIdx < m_iSoftKeyMax ; mIdx++)
    {
        pBtnGroup[mIdx] = new CButtonStable(this);
        pBtnGroup[mIdx]->setVisible(false);
    }
}
void CKeyBase8::KeyBtnSlotInit()
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

void CKeyBase8::motionKeyPressed()
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
void CKeyBase8::motionKeyReleased()
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
