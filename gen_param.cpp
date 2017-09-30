#include "gen_param.h"
#include "resource_manager.h"

#define BTN_IDX_NULL        ( -1 )

CGenParam::CGenParam(int mPf,int type,int page, QWidget *parent) :
    QWidget(parent)
{

    setObjectName("CGenParam");

    for(int mIdx = 0 ; mIdx < PARAM_MAX; mIdx++)
    {
        pBtnGroup[mIdx] = new CButtonStable(this);
        connect(pBtnGroup[mIdx],SIGNAL(pressed()),this,SLOT(OnParamPress()) );
        pBtnGroup[mIdx]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_003"));
        pBtnGroup[mIdx]->setFlat(true);
    }

    switch(mPf)
    {
    case PF_CEIL_10_A:
    case PF_CEIL_10_B:
    case PF_UARM_10_A:
    case PF_RAIL_12_A:
        resize(SYS_HEI(305),SYS_WID(457));
        pBtnGroup[0]->setGeometry(SYS_HEI(1),SYS_WID(1),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[1]->setGeometry(SYS_HEI(1),SYS_WID(77),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[2]->setGeometry(SYS_HEI(1),SYS_WID(153),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[3]->setGeometry(SYS_HEI(1),SYS_WID(229),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[4]->setGeometry(SYS_HEI(1),SYS_WID(305),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[5]->setGeometry(SYS_HEI(1),SYS_WID(381),SYS_HEI(100),SYS_WID(75));

        pBtnGroup[6]->setGeometry(SYS_HEI(102),SYS_WID(1),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[7]->setGeometry(SYS_HEI(102),SYS_WID(77),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[8]->setGeometry(SYS_HEI(102),SYS_WID(153),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[9]->setGeometry(SYS_HEI(102),SYS_WID(229),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[10]->setGeometry(SYS_HEI(102),SYS_WID(305),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[11]->setGeometry(SYS_HEI(102),SYS_WID(381),SYS_HEI(100),SYS_WID(75));

        pBtnGroup[12]->setGeometry(SYS_HEI(203),SYS_WID(1),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[13]->setGeometry(SYS_HEI(203),SYS_WID(77),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[14]->setGeometry(SYS_HEI(203),SYS_WID(153),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[15]->setGeometry(SYS_HEI(203),SYS_WID(229),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[16]->setGeometry(SYS_HEI(203),SYS_WID(305),SYS_HEI(100),SYS_WID(75));
        pBtnGroup[17]->setGeometry(SYS_HEI(203),SYS_WID(381),SYS_HEI(100),SYS_WID(75));
        break;
    case PF_CEIL_08_A:
    case PF_UARM_08_A:
    case PF_RAIL_08_A:
        resize(SYS_WID(305),SYS_HEI(457));
        pBtnGroup[0]->setGeometry(SYS_WID(1),SYS_HEI(1),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[1]->setGeometry(SYS_WID(1),SYS_HEI(77),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[2]->setGeometry(SYS_WID(1),SYS_HEI(153),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[3]->setGeometry(SYS_WID(1),SYS_HEI(229),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[4]->setGeometry(SYS_WID(1),SYS_HEI(305),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[5]->setGeometry(SYS_WID(1),SYS_HEI(381),SYS_WID(100),SYS_HEI(75));

        pBtnGroup[6]->setGeometry(SYS_WID(102),SYS_HEI(1),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[7]->setGeometry(SYS_WID(102),SYS_HEI(77),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[8]->setGeometry(SYS_WID(102),SYS_HEI(153),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[9]->setGeometry(SYS_WID(102),SYS_HEI(229),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[10]->setGeometry(SYS_WID(102),SYS_HEI(305),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[11]->setGeometry(SYS_WID(102),SYS_HEI(381),SYS_WID(100),SYS_HEI(75));

        pBtnGroup[12]->setGeometry(SYS_WID(203),SYS_HEI(1),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[13]->setGeometry(SYS_WID(203),SYS_HEI(77),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[14]->setGeometry(SYS_WID(203),SYS_HEI(153),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[15]->setGeometry(SYS_WID(203),SYS_HEI(229),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[16]->setGeometry(SYS_WID(203),SYS_HEI(305),SYS_WID(100),SYS_HEI(75));
        pBtnGroup[17]->setGeometry(SYS_WID(203),SYS_HEI(381),SYS_WID(100),SYS_HEI(75));
        break;
    default:
        break;
    }

    m_iParamType = type;
    m_val        = BTN_IDX_NULL;

    ParamInit(type,page);

    translateFontSize( this );
    setVisible(false);
}

void CGenParam::ParamInit(int type,int page)
{
    QString     * pStrDisplay;

    if(type >= PARAM_TYPE_MAX)
        return;

    switch(type)
    {
    case TYPE_MS:
        if(page >= GEN_MS_PAGE)
            return;

        m_iPageCur = page;
        pStrDisplay = &mMsList[ m_iPageCur * PARAM_MAX];

        break;
    case TYPE_KV:
        if(page >= GEN_KV_PAGE)
            return;

        m_iPageCur = page;
        pStrDisplay = &mKvList[ m_iPageCur * PARAM_MAX];
        break;
    case TYPE_MA:
        if(page >= GEN_MA_PAGE)
            return;

        m_iPageCur = page;
        pStrDisplay = &mMaList[ m_iPageCur * PARAM_MAX];
        break;
    case TYPE_MAS:
        if(page >= GEN_MAS_PAGE)
            return;

        m_iPageCur = page;
        pStrDisplay = &mMasList[ m_iPageCur * PARAM_MAX];
        break;
    default:
        return;
    }

    for(int mIdx = 0 ; mIdx < PARAM_MAX ; mIdx++)
    {
        pBtnGroup[mIdx]->setText(pStrDisplay[mIdx]);
        if(pStrDisplay[mIdx] == "")
            pBtnGroup[mIdx]->setVisible(false);
    }

}
void CGenParam::showEvent(QShowEvent *)
{
    if((m_val != BTN_IDX_NULL) && (m_val < PARAM_MAX))
        pBtnGroup[m_val]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_004"));

    RsMgr->VisibleWidgetAdd(this);
}
void CGenParam::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}
void CGenParam::KeyClear(int )
{
    if((m_val != BTN_IDX_NULL) && (m_val < PARAM_MAX))
        pBtnGroup[m_val]->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_STR_BTN_003"));
    m_val = BTN_IDX_NULL;

}
void CGenParam::KeySet(int keyIdx)
{
    if((keyIdx != BTN_IDX_NULL) && (keyIdx < PARAM_MAX))
        m_val = keyIdx;

}

void CGenParam::OnParamPress()
{
    for(int mIdx = 0 ; mIdx < PARAM_MAX; mIdx++)
    {
        if( sender() == pBtnGroup[mIdx] )
        {
            emit ParamChange( m_iParamType, m_iPageCur * PARAM_MAX + mIdx);

            m_val = mIdx;
            break;
        }
    }
}
int CGenParam::GetMaIndexPadding(int idx)
{

    if(idx > 40 )
        return idx + 12;
    else
        return idx;

}
int CGenParam::GetMaIndexRepare(int idx)
{
    int mIdx = 0;
    QString mBuf = mMaList[idx];

    while(mMaList[mIdx] != "")
    {

        if(mBuf == mMaList[mIdx])
        {
            if(mIdx > 40 )
                return mIdx - 12;           //去掉重复的内容
            else
                return mIdx;
        }

        mIdx++;
    }

    return idx;
}

int CGenParam::GetMsIndexPadding(int idx)
{

    if(idx >= 72 )
        return idx + 11;
    else
        return idx;

}
int CGenParam::GetMsIndexRepare(int idx)
{
    int mIdx = 0;
    QString mBuf = mMsList[idx];

    while(mMsList[mIdx] != "")
    {

        if(mBuf == mMsList[mIdx])
        {
            if(mIdx > 72 )
                return mIdx - 11;           //去掉重复的内容
            else
                return mIdx;
        }
        mIdx++;
    }

    return idx;
}

int CGenParam::GetMasIndex(int idx)
{

    int mIdx = 0;
    QString mBuf = mMasList[idx];

    while(mMasList[mIdx] != "")
    {
        if(mBuf == mMasList[mIdx])
        {
            return mIdx;
        }
        mIdx++;
    }

    return idx;
}

int CGenParam::GetKvIndex(int mKv)
{
    int mIdx = 0;

    while(mKvList[mIdx] != "")
    {
        if(mKv == mKvList[mIdx].toInt())
        {
            return mIdx;
        }

        mIdx++;
    }

    return mKv;
}
QString CGenParam::mMsList[]={
    "1.0", "1.1",  "1.2", "1.4", "1.6", "1.8", "2.0", "2.2", "2.5", "2.8", "3.2", "3.6",  "4.0", "4.5", "5.0", "5.6", "6.3", "7.1",
    "8.0", "9.0",  "10",  "11",  "12.5","14",  "16",  "18",  "20",  "22",  "25",  "28",   "32",  "36",  "40",  "45",  "50",  "56",
    "63",  "71",   "80",  "90",  "100", "110", "125", "140", "160", "180", "200", "220",  "250", "280", "320", "360", "400", "450",
    "500", "560",  "630", "710", "800", "900", "1000","1100","1250","1400","1600","1800","2000", "2200","2500","2800","3200","3600",
    "1100","1250","1400","1600","1800","2000", "2200","2500","2800","3200","3600","4000", "4500","5000","5600","6300" ,""    ,""
};

QString CGenParam::mMasList[]={
    "0.1", "0.2", "0.3", "0.4", "0.5", "0.6", "0.7", "0.8", "0.9", "1",  "1.1", "1.2", "1.4", "1.6", "1.8", "2" ,  "2.2", "2.5" ,
    "2.8", "3.2", "3.6", "4.0", "4.5", "5" ,  "5.6", "6.3", "7.1", "8",  "9",   "10",  "11",  "12.5","14",  "16" , "18",  "20" ,
    "22" , "25" , "28" , "32" , "36" , "40" , "45" , "50" , "56",  "63", "71",  "80",  "90",  "100", "110", "125", "140", "160" ,
    "180", "200", "220", "250", "280", "320", "360", "400","450", "500", "560", "630", "710", "800", "900", "1000",""   , ""
};

QString CGenParam::mMaList[]={
    "10" , "11" , "12.5", "14" , "16" , "18" , "20" , "22" , "25" , "28" , "32" , "36" , "40" ,  "45" , "50" , "56" , "63" , "71" ,
    "80" , "90" , "100" , "110", "125", "140", "160", "180", "200", "220", "250", "280", "320",  "360", "400", "450", "500", "560",
    "160", "180", "200" , "220", "250", "280", "320", "360", "400", "450", "500", "560", "630",  "710", "800", "900", "1000",""
};

QString CGenParam::mKvList[]={
    "40" , "41",  "42" , "43",  "44" , "45" , "46" , "47" , "48" , "49" , "50" , "51" , "52" ,  "53" , "54" , "55" , "56" , "57" ,
    "58" , "59",  "60" , "61",  "62" , "63" , "64" , "65" , "66" , "67" , "68" , "69" , "70" ,  "71" , "72" , "73" , "74" , "75" ,
    "76" , "77",  "78" , "79",  "80" , "81" , "82" , "83" , "84" , "85" , "86" , "87" , "88" ,  "89" , "90" , "91" , "92" , "93" ,
    "94" , "95",  "96" , "97",  "98" , "99" , "100", "101", "102", "103", "104", "105", "106",  "107", "108", "109", "110", "111",
    "112", "113", "114", "115", "116", "117", "118", "119", "120", "121", "122", "123", "124",  "125", "126", "127", "128", "129",
    "130", "131", "132", "133", "134", "135", "136", "137", "138", "139", "140", "141", "142",  "143", "144", "145", "146", "147",
    "136", "137", "138", "139", "140", "141", "142", "143", "144", "145", "146", "147", "148",  "149", "150", ""   , ""   , ""
};

