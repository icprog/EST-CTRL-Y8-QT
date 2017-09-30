#include "sim_base.h"
#include "resource_manager.h"

CSimBase::CSimBase(QWidget *parent) :
    QWidget(parent)
{

    btnSim      = new CButtonStable();
    sceneSim    = new QGraphicsScene(this);
    viewSim     = new QGraphicsView(this);

    viewSim->setFocusPolicy(Qt::NoFocus);
    viewSim->setFrameShape(QFrame::NoFrame);
    viewSim->setFrameShadow(QFrame::Plain);
    viewSim->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    viewSim->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    timerSimFresh = new QTimer(this);
    timerSimFresh->setInterval(TIME_SIM_FRESH);
    connect(timerSimFresh,SIGNAL(timeout()),this,SLOT(OnSimFresh()));

    btnSim->setText(QApplication::translate("CSimBase", "Demo\nOFF"));
    connect(btnSim,SIGNAL(pressed()),this,SLOT(OnSimPressed()));
    btnSim->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_OFF"));

    QFont font;
    font.setPixelSize(SYS_FONT(18));
    btnSim->setFont(font);

    setStyleSheet("background : transparent");

    setVisible(false);
}

void CSimBase::showEvent(QShowEvent *)
{
    RsMgr->VisibleWidgetAdd(this);
}
void CSimBase::hideEvent(QHideEvent *)
{
    RsMgr->VisibleWidgetDel(this);
}
void CSimBase::mousePressEvent(QMouseEvent */*event*/)
{

    qDebug()<<"CSimBase::mousePressEvent";

}
void CSimBase::OnViewDirChange(int )
{
}
void CSimBase::SimulateDataInit()
{

}
void CSimBase::OnComKeyCommand(unsigned short mkey)
{
    OnSimulateKey(mkey);
}

void CSimBase::OnSimulateKey(int)
{

}

void CSimBase::OnSimFresh()
{
    int m_TempFinished = true;

    for(int mIdx = 0; mIdx < m_iMotionMax ; mIdx++)
    {
        if(m_iMotor[mIdx][MOTOR_POS_FLG])
        {
            m_TempFinished = false;

            m_iMotor[mIdx][MOTOR_POS_DAT] += m_iMotor[mIdx][MOTOR_POS_DIR] * m_iMotor[mIdx][MOTOR_POS_STEP];

            if( m_iMotor[mIdx][MOTOR_POS_DIR] == -1)
            {
                if(m_iMotor[mIdx][MOTOR_POS_DAT] <= m_iMotor[mIdx][MOTOR_POS_TAR] )
                {
                    m_iMotor[mIdx][MOTOR_POS_FLG] = 0;
                    m_iMotor[mIdx][MOTOR_POS_DAT] = m_iMotor[mIdx][MOTOR_POS_TAR];
                }
            }else if( m_iMotor[mIdx][MOTOR_POS_DIR] == 1)
            {
                if(m_iMotor[mIdx][MOTOR_POS_DAT] >= m_iMotor[mIdx][MOTOR_POS_TAR] )
                {
                    m_iMotor[mIdx][MOTOR_POS_FLG] = 0;
                    m_iMotor[mIdx][MOTOR_POS_DAT] = m_iMotor[mIdx][MOTOR_POS_TAR];
                }
            }

            g_systemDb->g_dbMachine.CurrentData[mIdx] = m_iMotor[mIdx][MOTOR_POS_DAT];
        }
    }

    if( m_TempFinished)
    {
        g_systemDb->g_dbMachine.CurrentData[16] = 1;
        g_systemDb->g_dbMachine.CurrentData[17] = 1;
        g_systemDb->g_dbMachine.CurrentData[18] = 1;
        timerSimFresh->stop();
    }
}

void CSimBase::OnSimPressed()
{

    if(sender() == btnSim)
    {
        if( g_systemDb->g_bMotionSimulate)
        {
            g_systemDb->g_bMotionSimulate = false;
            btnSim->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_OFF"));
            btnSim->setText(QApplication::translate("CSimBase", "Demo\nOFF"));
            emit InfoMsgCtrl(INFO_CTRL_DEL,MSG_MODE_DEMO);
        }else
        {
            g_systemDb->g_bCommunicate = true;
            g_systemDb->g_bMotionSimulate = true;

            g_systemDb->g_dbMachine.StateData[0] = 0;
            g_systemDb->g_dbMachine.StateData[1] = 0;
            g_systemDb->g_dbMachine.StateData[4] = 0xffff;

            for(int mIdx = 0 ;mIdx < m_iMotionMax ;mIdx++)
            {
                m_iMotor[mIdx][MOTOR_POS_DAT] = g_systemDb->g_dbMachine.CurrentData[mIdx];
            }

            btnSim->setStyleSheet(g_skinBase->GetStyleMapStr("SYS_SIM_ON"));
            btnSim->setText(QApplication::translate("CSimBase", "Demo\nON"));
            emit InfoMsgCtrl(INFO_CTRL_ADD,MSG_MODE_DEMO);
        }
    }
}
