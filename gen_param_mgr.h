#ifndef GEN_PARAM_MGR_H
#define GEN_PARAM_MGR_H

#include <QWidget>
#include "system_defines.h"
#include "gen_param.h"


class CGenParamMgr : public QWidget
{
    Q_OBJECT
    
public:
    explicit CGenParamMgr(int mPf,QWidget *parent = 0);

    void ShowType(int type);

    CButtonStable *btPre;
    CButtonStable *btNext;
protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    CGenParam * m_iFrames[GEN_KV_PAGE + GEN_MA_PAGE + GEN_MAS_PAGE + GEN_MS_PAGE];
    int m_iTypeCur;
    int m_iPageKv;
    int m_iPageMa;
    int m_iPageMs;
    int m_iPageMas;
    int m_iPageDisplay;
    int m_iPageNew;

    int m_iPageKvLast;
    int m_iPageMaLast;
    int m_iPageMsLast;
    int m_iPageMasLast;

private slots:
    void OnPageChange();
    void OnParamShow(int);
    void OnParamChange(int,int);
    void OnBodyIndexChange(int );

signals:
    void PopupShow(int);
    void PopupHide(QWidget *);
};

#endif // GEN_PARAM_MGR_H
