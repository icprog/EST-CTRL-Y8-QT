#include "frame_ceil8_key.h"
#include "resource_manager.h"

CFrameCeil8Key::CFrameCeil8Key(QWidget *parent) :
    CFrameKeyBase(parent),Ui_CFrameKeyBase()
{
    setupUi(this);
    translateFontSize(this);

    m_keyMax = CEIL8_KEY_MAX;
    g_keyPtr = &g_keyCeil8;
}
