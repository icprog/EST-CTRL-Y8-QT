#include <QSettings>
#include <QFileInfo>

#include "resource_manager.h"
#include "face_base12.h"

CFaceBase12::CFaceBase12( QWidget* parent):
    CFaceBase(parent)
{

    setObjectName("CFaceBase12");

    resize(g_sysWidth,g_sysHeight);

    QFont font;
    font.setPixelSize(SYS_FONT(24));

    QSettings * configClientInfo = new QSettings(QCoreApplication::applicationDirPath() + "/clientinfo.ini",QSettings::IniFormat);
    QString hostpitalName = "    ";
    hostpitalName  += QString::fromUtf8(configClientInfo->value("/client/HospitalName","伊士通(上海)医疗器械有限公司").toByteArray());

    hostpitalName += "\n                                        v:";

    hostpitalName += g_dbsys.softVersion;

    hostpitalName += "\n                                        d:";

    QFileInfo * pMainProgramInfo = new QFileInfo(QCoreApplication::applicationFilePath());
    QDateTime mDate = pMainProgramInfo->lastModified();

    hostpitalName += mDate.toString(Qt::ISODate).left(10);

    stHospital->setFont(font);
    stHospital->setText(hostpitalName);

    infoView->setGeometry(SYS_WID(100),0,SYS_WID(50),g_sysHeight);
    infoView->rotate(90);
    infoView->setVisible(false);

    progressBar->setStyleSheet("QProgressBar{ background:transparent; text-align: center;color:blue}"
                               "QProgressBar::chunk {background-color: green;width: 10px;margin: 1px;}");
    progressBar->setGeometry(SYS_WID(38 ), SYS_HEI(12),  SYS_WID(320), SYS_HEI(32));
    barView->setGeometry(SYS_WID(574 ),0,SYS_WID(60),g_sysHeight);
    barView->rotate(90);

    versionView->setGeometry(SYS_WID(680 ),0,SYS_WID(100),g_sysWidth);
    versionView->rotate(90);
    versionView->setVisible(false);
}


