#include "curtain_base10.h"
#include "resource_manager.h"

CCurtainBase10::CCurtainBase10(QWidget *parent) :
    CCurtainBase(parent)
{

    setObjectName("CCurtainBase10");

    resize(SYS_WID(90),SYS_HEI(90));

    pbCurtainSwitch->setGeometry(SYS_HEI(0),SYS_WID(0),SYS_HEI(65),SYS_WID(65));


    sceneCurtain    = new QGraphicsScene(this);
    viewCurtain     = new QGraphicsView(this);

    viewCurtain->setFocusPolicy(Qt::NoFocus);
    viewCurtain->setFrameShape(QFrame::NoFrame);
    viewCurtain->setFrameShadow(QFrame::Plain);
    viewCurtain->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewCurtain->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);


    sceneCurtain->addWidget(pbCurtainSwitch);

    viewCurtain->setScene(sceneCurtain);
    viewCurtain->setGeometry(SYS_HEI(0),SYS_WID(0),SYS_HEI(70),SYS_WID(70));
    viewCurtain->rotate(90);

    setGeometry(SYS_HEI(625),SYS_WID(13), SYS_HEI(70),SYS_WID( 70));
}

void CCurtainBase10::OnViewDirChange(int m_iViewDir)
{
    int m_rotAngle = 0;
    switch(m_iViewDir)
    {
    case VIEW_DIR_NORMAL:
        m_rotAngle = 90;
        break;
    case VIEW_DIR_LEFT:
        m_rotAngle = 0;
        break;
    case VIEW_DIR_RIGHT:
        m_rotAngle = 180;
        break;
    case VIEW_DIR_R180:
        m_rotAngle = 0;
        break;
    default:
        return;
    }
    viewCurtain->resetTransform();
    viewCurtain->rotate(m_rotAngle);

}
