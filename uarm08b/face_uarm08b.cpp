#include "./sys/system_defines.h"
#ifdef USE_RAIL_08_B

#include <QSettings>
#include <QFileInfo>

#include "resource_manager.h"
#include "face_rail08b.h"

CFaceRail08b::CFaceRail08b( QWidget* parent):
    CFaceBase8(parent)
{
    setObjectName("CFaceRail08b");   

    OnViewDirChange(g_systemDb->g_startAngle);
}

void CFaceRail08b::OnViewDirChange(int sAngle)
{
    CFaceBase8::OnViewDirChange(sAngle);

    switch(sAngle)
    {
    case VIEW_DIR_NORMAL:
        progressBar->setGeometry(SYS_WID(0 ), SYS_HEI(12),  SYS_WID(258), SYS_HEI(26));
        faceView->setGeometry(SYS_WID(2 ),SYS_HEI(260 ),g_sysWidth,SYS_HEI(50));
        break;
    case VIEW_DIR_LEFT:
        progressBar->setGeometry(SYS_HEI(0 ), SYS_HEI(12),  SYS_HEI(258), SYS_WID(26));
        faceView->setGeometry(SYS_WID(306 ),SYS_HEI(0),SYS_WID(50),g_sysHeight);
        faceView->rotate(-90);
        break;
    case VIEW_DIR_RIGHT:
        progressBar->setGeometry(SYS_HEI(0 ), SYS_WID(12),  SYS_HEI(258), SYS_WID(26));
        faceView->setGeometry(SYS_WID(445 ),SYS_WID(0),SYS_WID(50),g_sysHeight);
        faceView->rotate(90);
        break;
    case VIEW_DIR_R180:
        progressBar->setGeometry(SYS_WID(0 ), SYS_HEI(12),  SYS_WID(258), SYS_HEI(26));
        faceView->setGeometry(SYS_WID(0 ),SYS_HEI(290 ),g_sysWidth,SYS_HEI(50));
        faceView->rotate(180);
        break;
    default:
        progressBar->setGeometry(SYS_HEI(0 ), SYS_WID(12),  SYS_HEI(258), SYS_WID(26));
        faceView->setGeometry(SYS_WID(0 ),SYS_HEI(260 ),g_sysWidth,SYS_HEI(50));
        break;

    }

}
#endif //USE_RAIL_08_B
