#include "smart_uarm10.h"
#include "resource_manager.h"

CSmartUarm10::CSmartUarm10(QWidget *parent) :
    CSmartBase10(parent)
{
    setObjectName("CSmartUarm10");

    QFont font;
    font.setPixelSize(SYS_FONT(22));

    mSmartMax = UARM10_SMART_MAX;

    pBtnGroup[0]->setText(QApplication::translate("CSmartBase", "Free Move"));
    pBtnGroup[1]->setText(QApplication::translate("CSmartBase", "Stand 1.8m"));
    pBtnGroup[2]->setText(QApplication::translate("CSmartBase", "Stand 1.1m"));
    pBtnGroup[3]->setText(QApplication::translate("CSmartBase", "Stand Slash"));
    pBtnGroup[4]->setText(QApplication::translate("CSmartBase", "Stand Slash"));
    pBtnGroup[5]->setText(QApplication::translate("CSmartBase", "Table"));
    pBtnGroup[6]->setText(QApplication::translate("CSmartBase", "Table Slash"));

    QRect rectTemp = pBtnGroup[7]->geometry();

    for(int mIdx = mSmartMax - 1; mIdx > 0 ; mIdx--)
    {
        pBtnGroup[mIdx]->setGeometry(pBtnGroup[mIdx - 1]->geometry());
        pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1 + mIdx));
        pBtnGroup[mIdx]->setFont(font);
    }

    pBtnGroup[0]->setGeometry(rectTemp);
    pBtnGroup[0]->setStyleSheet(g_skinBase->GetStyleMapStr(SYS_SMART_BASE1));

}
