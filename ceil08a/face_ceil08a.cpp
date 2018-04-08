#include "face_ceil08a.h"

#ifdef USE_CEIL_08_A


CFaceCeil08a::CFaceCeil08a( QWidget* parent):
    CFaceBase8(parent)
{
    setObjectName("CFaceCeil08a");

    OnViewDirChange(g_sysDb->g_startAngle);

    ipAddrDisplay->setVisible(true);
    ipAddrDisplay->setGeometry(QRect(636, 568, 164, 32));
}

void CFaceCeil08a::OnViewDirChange(TypeViewDir sAngle)
{
    CFaceBase8::OnViewDirChange(sAngle);

    switch(sAngle)
    {
    case VDirNORM:
        progressBar->setGeometry(SYS_HEI(0 ), SYS_WID(12),  SYS_HEI(258), SYS_WID(32));
        faceView->setGeometry(SYS_WID(6 ),SYS_HEI(550 ),g_sysWidth,SYS_HEI(50));
        break;
    case VDirLEFT:
        progressBar->setGeometry(SYS_HEI(0 ), SYS_WID(12),  SYS_HEI(258), SYS_WID(32));
        faceView->setGeometry(SYS_WID(456 ),SYS_WID(8),SYS_WID(50),g_sysHeight);
        faceView->rotate(90);
        break;
    case VDirRIGHT:
        progressBar->setGeometry(SYS_HEI(0 ), SYS_WID(11),  SYS_HEI(320), SYS_WID(32));
        faceView->setGeometry(SYS_WID(0 ),SYS_HEI(376 ),g_sysWidth,SYS_HEI(60));
        faceView->rotate(180);
        break;
    case VDirREVERSE:
        break;
    default:
        break;

    }

}
#endif
