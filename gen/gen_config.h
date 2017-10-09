#ifndef GEN_CONFIG_H
#define GEN_CONFIG_H

#include <QWidget>
#include <QLabel>
#include <QGraphicsView>
#include <QGraphicsScene>

#include "./base/button_stable.h"
#include "./system/system_defines.h"

#define CFG_MAX_TECH        3
#define CFG_INFO_MAX        6
#define CFG_DIR_MAX         4
#define CFG_POSITION_MAX    4


class CGenConfig : public QWidget
{
    Q_OBJECT
    
public:
    explicit CGenConfig(QWidget *parent = 0);


public:
    QGraphicsView *viewPopup;
    QGraphicsView *viewGen;
    QGraphicsScene  * pSceneArray[POPUP_CFG_MAX];       //场景，KV,MA,AEC,Focus

protected:
    void showEvent(QShowEvent *);
    void hideEvent(QHideEvent *);

private:
    QLabel * m_lbTitle;
    CButtonStable * btSave;
    CButtonStable * btExit;
    CButtonStable * pBtnGroup[CFG_MAX_TECH];
    int m_iViewDir;
    int m_iLastTech;
    QRect PopInfoPos[POPUP_CFG_MAX];

    void myPopupPosInit();

public slots:
    void OnButtonClick();                  //导航按键处理
    void OnGenTechChange();                //发生器参数改变

    void OnPopupHide(QWidget *);
    void OnPopupShow(int);

signals:
    void GenTechChange(int tech);
    void ViewChange(int view);
};

#endif // GEN_CONFIG_H
