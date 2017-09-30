#include "system_console1.h"
#include "resource_manager.h"

CSystemConsole1::CSystemConsole1( QWidget* parent ):
    QWidget(parent)
{     
    setObjectName("CSystemConsole1");

    resize(800,600);

    outBufferFile = QCoreApplication::applicationDirPath() + "/outBuffer";

    QFont font;
    font.setPixelSize(16);

    pInputBox = new QLabel(this);
    pInputBox->setGeometry(0,0,800,40);
    pInputBox->setStyleSheet("background-color:white;border:1px solid blue");
    pInputBox->setFont(font);

    pDispbox = new QTextEdit(this);
    pDispbox->setGeometry(0,40,800,560);
    pDispbox->setFont(font);
    pDispbox->ensureCursorVisible();
    pDispbox->setStyleSheet("background-color:white;border:1px solid green");

    mDispboxLines = 0;

    setVisible(false);
}


void CSystemConsole1::showEvent(QShowEvent * event)
{  

    grabKeyboard();

    pInputBox->setText(dirManager.currentPath() + '#' +mBufInput);

    QWidget::showEvent(event);
}

void CSystemConsole1::hideEvent(QHideEvent *event)
{

    releaseKeyboard();

    QWidget::hideEvent(event);
}


bool CSystemConsole1::eventFilter(QObject *watched, QEvent *event)
{
    event->accept();

    return QWidget::eventFilter(watched,event);
}

void CSystemConsole1::keyPressEvent ( QKeyEvent * event )
{
    event->accept();
    int mchar;

    int mKey = event->key();

    switch (mKey)
    {
    case Qt::Key_Return:
    case Qt::Key_Enter:
        RunAndDisp();
        MoveCursorEnd();
        break;
    case Qt::Key_PageUp:
        pDispbox->moveCursor(QTextCursor::Up);
        break;
    case Qt::Key_PageDown:
        pDispbox->moveCursor(QTextCursor::Down);
        break;
    case Qt::Key_Home:
        pDispbox->moveCursor(QTextCursor::Start);
        break;
    case Qt::Key_End:
        pDispbox->moveCursor(QTextCursor::End);
        break;
    case Qt::Key_Backspace:
        mBufInput.chop( 1);
        break;
    case Qt::Key_Escape:
        break;
    case Qt::Key_Tab:
        break;
    default:
        mchar = *(event->text().toStdString().c_str());

        if(isprint(mchar))
            mBufInput.append(event->text());

        break;
    }

    pInputBox->setText(dirManager.currentPath() + '#' +mBufInput);
}
void CSystemConsole1::RunAndDisp()
{
    QString cmdCD("cd ");

    /*analysis user input*/
    int CmdLen = mBufInput.length();
    if(CmdLen == 0)
        return;

    //ftp
    if(mBufInput.left(4).compare("ftp ") == 0)
        return;

    //top
    if(mBufInput.left(3).compare("top") == 0)
        return;

    //ping
    if(mBufInput.left(4).compare("ping") == 0)
        return;

    if(mBufInput.left(cmdCD.length()).compare(cmdCD) == 0)     //user change current dir
    {
        QString dirChangeTo(mBufInput.right(CmdLen - cmdCD.length()));

        bool dirChanged = dirManager.cd(dirChangeTo);

        if(dirChanged)
        {
            dirChanged = QDir::setCurrent(dirManager.absolutePath());
        }

        pDispbox->append("<span style=' color:#0000ff;'>"+ dirManager.currentPath() + '#' + mBufInput + "</span>");
        mDispboxLines ++;

        mBufInput = "";
        return;
    }

    pDispbox->append("<span style=' color:#0000ff;'>"+ dirManager.currentPath() + '#' + mBufInput + "</span>");
    mDispboxLines ++;

    mBufInput += " > " + outBufferFile;

    /*run user command*/
    int mRes = system(mBufInput.toStdString().c_str());

    if(mRes >= 0)
        mBufInput = "";

    /*display execute result*/
    QFile data(outBufferFile);
    if (data.open(QFile::ReadOnly ))
    {
        QTextStream res(&data);
        while(!res.atEnd())
        {
            pDispbox->append(res.readLine());
            mDispboxLines ++;

            if(mDispboxLines >= 4096)
            {
                pDispbox->clear();
                mDispboxLines = 0;
            }
        }

        data.close();
    }

}

void CSystemConsole1::MoveCursorEnd()
{
    QTextCursor cursor =  pDispbox->textCursor();
    cursor.movePosition(QTextCursor::End);
    pDispbox->setTextCursor(cursor);
}
