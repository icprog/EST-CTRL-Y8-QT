#include "film_base10.h"
#include "resource_manager.h"


CFilmBase10::CFilmBase10(QWidget *parent) :
    CFilmBase(parent)
{
    connect(timerFilmLong,SIGNAL(timeout()),this,SLOT(OnTimerFilmLong()));
}
void CFilmBase10::SendCmdKey(int )
{

}

void CFilmBase10::OnTimerFilmLong()
{
    // emit SmartChange(m_keyTag);
    SendCmdKey(m_keyTag);
    SetKeySound();
}
