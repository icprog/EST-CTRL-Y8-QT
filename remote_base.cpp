#include "remote_base.h"
#include "resource_manager.h"

CRemoteBase::CRemoteBase(QWidget *parent) :
    CSystemBase(parent)
{

    connect(btnExit,SIGNAL(pressed()),this,SLOT(OnBtnExit()));

}

void CRemoteBase::OnBtnExit()
{
    this->hide();
    g_mainSetting->setSceneWidget(RsMgr->g_systemNetWork);

}
