#include "remote_server.h"
#include "resource_manager.h"

CRemoteServer::CRemoteServer(QWidget *parent) :
    CRemoteBase(parent)
{
    setObjectName("CRemoteServer");

    resize(600,600);

    textTitle->setText(QApplication::translate("CRemoteBase", "Remote Controller Setting"));

    translateFontSize( this );
}
