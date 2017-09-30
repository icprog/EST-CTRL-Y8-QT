#ifndef FRAME_GEN_PARAM_H
#define FRAME_GEN_PARAM_H

#include <QWidget>

#include "button_stable.h"

#define PARAM_MAX       ( 18 )


class CGenParam : public QWidget
{
    Q_OBJECT
    
public:

    CGenParam(int mPf,int paramType,int page,QWidget *parent = 0);

    void KeyClear(int keyIdx);
    void KeySet(int keyIdx);

    static QString mKvList[];
    static QString mMaList[];
    static QString mMasList[];
    static QString mMsList[];

    static int GetMaIndexRepare(int);   //主要为了去掉重复的内容
    static int GetMaIndexPadding(int);  //主要为了适应Ms数组

    static int GetMsIndexRepare(int);   //主要为了去掉重复的内容
    static int GetMsIndexPadding(int);  //主要为了适应Ms数组

    static int GetMasIndex(int);   //主要为了去掉重复的内容

    static int GetKvIndex(int);         //40-150  变换到 0-111

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    int m_iParamType;                       //类型,kv,ma,mas,ms
    int m_iPageCur;                         //当前显示的页码
    int m_val;                              //被选择的按钮的序号

    CButtonStable * pBtnGroup[PARAM_MAX];

    void ParamInit(int type,int page);

private slots:
    void OnParamPress();

signals:
    void ParamChange(int type,int idx);
};

#endif // FRAME_GEN_PARAM_H
