#include "gen_client.h"
#include "resource_manager.h"

// PACKET ID
#define UDP_POS_HEADER1			 0
#define UDP_POS_HEADER2			 1
#define UDP_POS_ADDRESS			 2
#define UDP_POS_COMMAND			 3
#define UDP_POS_DATA1			 4
#define UDP_POS_DATA2			 5
#define UDP_POS_DATA3			 6
#define UDP_POS_DATA4			 7
#define UDP_POS_DATA5			 8
#define UDP_POS_DATA6			 9
#define UDP_POS_DATA7			10
#define UDP_POS_DATA8			11
#define UDP_POS_CHECKSUM		12
#define UDP_POS_TAIL			13

// Set Command
#define UDP_CMD_SET_RKVMATIME           0x0A
#define UDP_CMD_SET_RKV                 0x0B
#define UDP_CMD_SET_RMA                 0x0C
#define UDP_CMD_SET_RTIME               0x0D
#define UDP_CMD_SET_NO_BUCKY            0x15
#define UDP_CMD_SET_BUCKY1              0x16
#define UDP_CMD_SET_BUCKY2              0x17
#define UDP_CMD_SET_AEC                 0x1E
#define UDP_CMD_SET_AEC_ON              0x1F
#define UDP_CMD_SET_AEC_OFF             0x20
#define UDP_CMD_SET_AEC_FIELD_LEFT      0x24
#define UDP_CMD_SET_AEC_FIELD_CENTER    0x25
#define UDP_CMD_SET_AEC_FIELD_RIGHT     0x26
#define UDP_CMD_SET_AEC_FIELD_ALL       0x27
#define	UDP_CMD_SET_FOCAL_SPOT          0x60
#define	UDP_CMD_SET_TIME_MAS_SELECT     0x6E
#define	UDP_CMD_SET_2POINT_RKVMAS       0x73


// Update Command
#define UDP_CMD_UPDATE_RKVMATIME       0xC9
#define UDP_CMD_UPDATE_BUCKY           0xCA
#define UDP_CMD_UPDATE_AEC             0xCB
#define UDP_CMD_UPDATE_STATE           0xCD
#define UDP_CMD_UPDATE_RKV		       0xE0
#define UDP_CMD_UPDATE_RMA			   0xE1
#define UDP_CMD_UPDATE_RTIME		   0xE2
#define UDP_CMD_UPDATE_RMX			   0xE3
#define UDP_CMD_UPDATE_TIME_MAS_SELECT 0xE6
#define UDP_CMD_UPDATE_EXP_STATE       0xF0
#define UDP_CMD_UPDATE_HU_PERCENT      0xF1
#define UDP_CMD_UPDATE_EXP_CNT         0xF2
#define UDP_CMD_UPDATE_FOCAL_SPOT      0xF3
#define UDP_CMD_UPDATE_XRAY_EXP_CTRL   0xF4
#define UDP_CMD_UPDATE_FB_RKVMATIME    0xF5
#define UDP_CMD_UPDATE_WARNING         0xFD
#define UDP_CMD_UPDATE_ERROR           0xFE


CGenClient::CGenClient(QWidget *parent) :
    QWidget(parent)
{
    m_GenUdpClient = new QUdpSocket(this);
    m_GenUdpClient->bind(6000, QUdpSocket::ShareAddress);
    connect(m_GenUdpClient, SIGNAL(readyRead()),this, SLOT(processPendingDatagrams()));
}

void CGenClient::processPendingDatagrams()
{
    unsigned int mDatSize;

    while (m_GenUdpClient->hasPendingDatagrams())
    {
        mDatSize = m_GenUdpClient->readDatagram((char *)mUdpBufRead, UDP_PACKET_SIZE);

        if(!ServiceDataCheck((unsigned char *)mUdpBufRead,mDatSize))
            continue;

        switch(mUdpBufRead[UDP_POS_COMMAND])
        {
        case UDP_CMD_UPDATE_STATE:

            break;
        case UDP_CMD_UPDATE_RKVMATIME:
            emit ParamChange(TYPE_KV,CGenParam::GetKvIndex(mUdpBufRead[UDP_POS_DATA1]));
            emit ParamChange(TYPE_MA,CGenParam::GetMaIndexPadding(mUdpBufRead[UDP_POS_DATA2]));
            emit ParamChange(TYPE_MS,CGenParam::GetMsIndexPadding(mUdpBufRead[UDP_POS_DATA3]));
            emit ViewChange(VIEW_GEN);
            break;
        case UDP_CMD_UPDATE_RKV:
            emit ParamChange(TYPE_KV,mUdpBufRead[UDP_POS_DATA1]);
            break;
        case UDP_CMD_UPDATE_RMA:
            emit ParamChange(TYPE_MA,mUdpBufRead[UDP_POS_DATA1]);
            break;
        case UDP_CMD_UPDATE_RTIME:
            emit ParamChange(TYPE_MS,mUdpBufRead[UDP_POS_DATA1]);
            break;
        case UDP_CMD_UPDATE_RMX:
            emit ParamChange(TYPE_MAS,mUdpBufRead[UDP_POS_DATA1]);
            break;
        case UDP_CMD_UPDATE_BUCKY:
            //
            break;
        case UDP_CMD_UPDATE_AEC:
            //
            break;
        case UDP_CMD_UPDATE_TIME_MAS_SELECT:
            emit GenTechChange(mUdpBufRead[UDP_POS_DATA1] - 1);
            break;
        case UDP_CMD_UPDATE_FOCAL_SPOT:             //跟随发生器，切换焦点
            emit GenFocusChange(mUdpBufRead[UDP_POS_DATA1]);
            break;
        default:
            break;
        }
    }
}
//send data to real generator.
void CGenClient::OnGenAecChange(int )
{
    //UDP_CMD_SET_AEC_ON
    //UDP_CMD_SET_AEC_OFF
    //UDP_CMD_SET_AEC_FIELD_RIGHT
    //UDP_CMD_SET_AEC_FIELD_CENTER
    //UDP_CMD_SET_AEC_FIELD_LEFT
    //UDP_CMD_SET_AEC
    //mask aec mode now
    //SendCommand(UDP_CMD_SET_AEC,mFocus,0,0,0,0,0,0,0);
}
void CGenClient::OnGenFocusChange(int mFocus)
{

    SendCommand(UDP_CMD_SET_FOCAL_SPOT,mFocus,0,0,0,0,0,0,0);
}
void CGenClient::OnGenTechChange(int mTech)
{

    if(mTech == SYS_TECH_AEC )      //mask aec mode
        return;

    SendCommand(UDP_CMD_SET_TIME_MAS_SELECT,mTech + 1,0,0,0,0,0,0,0);

}

void CGenClient::OnParamChange(int type,int val)
{
    unsigned short mKv;

    switch(type)
    {
    case TYPE_KV:
        mKv = CGenParam::mKvList[val].toInt();
        SendCommand(UDP_CMD_SET_RKV,mKv,0,0,0,0,0,0,0);
        break;
    case TYPE_MA:
        SendCommand(UDP_CMD_SET_RMA,CGenParam::GetMaIndexRepare(val),0,0,0,0,0,0,0);
        break;
    case TYPE_MAS:
        SendCommand(UDP_CMD_SET_2POINT_RKVMAS,g_GenMain->GetGenKv(),CGenParam::GetMasIndex(val),0,0,0,0,0,0);
        break;
    case TYPE_MS:
        SendCommand(UDP_CMD_SET_RTIME,CGenParam::GetMsIndexRepare(val),0,0,0,0,0,0,0);
        break;
        //
        //UDP_CMD_SET_RKVMATIME
    }

    //SendCommand(UDP_CMD_SET_RKVMATIME, nVKV, nIMA, nIMS, 0, 0, 0, 0, 0);
}

void CGenClient::GenMsgNotify(int cmd,int )
{

    switch(cmd)
    {
    case UDP_CMD_UPDATE_RKVMATIME:

        break;
    case UDP_CMD_UPDATE_FOCAL_SPOT:
        break;
    case UDP_CMD_UPDATE_TIME_MAS_SELECT:

        break;
    case UDP_CMD_UPDATE_AEC:

        break;


    case UDP_CMD_UPDATE_FB_RKVMATIME:


    case UDP_CMD_UPDATE_EXP_STATE:

    case UDP_CMD_UPDATE_BUCKY:
        break;
    case UDP_CMD_UPDATE_HU_PERCENT:
        break;
    case UDP_CMD_UPDATE_ERROR:
        break;
    case UDP_CMD_UPDATE_WARNING:

        break;
    case UDP_CMD_UPDATE_STATE:

        break;
    default:
        break;
    }
}

bool CGenClient::ServiceDataCheck(unsigned char* pData, int nSize)
{
    unsigned char nCheckSum;
    if (nSize == 14)
    {
        nCheckSum = pData[UDP_POS_ADDRESS] ^
                pData[UDP_POS_COMMAND] ^
                pData[UDP_POS_DATA1] ^
                pData[UDP_POS_DATA2] ^
                pData[UDP_POS_DATA3] ^
                pData[UDP_POS_DATA4] ^
                pData[UDP_POS_DATA5] ^
                pData[UDP_POS_DATA6] ^
                pData[UDP_POS_DATA7] ^
                pData[UDP_POS_DATA8];

        //Check Header and Checksum Bytes
        if (pData[UDP_POS_HEADER1] == UDP_PACKET_HEADER1
                && pData[UDP_POS_HEADER2] == UDP_PACKET_HEADER2
                && nCheckSum == pData[UDP_POS_CHECKSUM])
        {
            return true;
        }
    }

    return false;
}

bool CGenClient::SendCommand(int nCommand, char nData1, char nData2, char nData3, char nData4, char nData5, char nData6, char nData7, char nData8)
{
    char	aBuffer[14];

    memset(&aBuffer, 0, sizeof(aBuffer));

    aBuffer[UDP_POS_HEADER1] = UDP_PACKET_HEADER1;			//Command Header Byte #1 : Fixed
    aBuffer[UDP_POS_HEADER2] = UDP_PACKET_HEADER2;			//Command Header Byte #2 : Fixed
    aBuffer[UDP_POS_ADDRESS] = UDP_PACKET_FROM_CLIENT;		//Command Type : 0x01(from Clinet to SDK) , 0x02(from SDK to Client)
    aBuffer[UDP_POS_COMMAND] = (char)nCommand;					//Command
    aBuffer[UDP_POS_DATA1] = nData1;						//Data1
    aBuffer[UDP_POS_DATA2] = nData2;						//Data2
    aBuffer[UDP_POS_DATA3] = nData3;						//Data3
    aBuffer[UDP_POS_DATA4] = nData4;						//Data4
    aBuffer[UDP_POS_DATA5] = nData5;						//Data5
    aBuffer[UDP_POS_DATA6] = nData6;						//Data6
    aBuffer[UDP_POS_DATA7] = nData7;						//Data7
    aBuffer[UDP_POS_DATA8] = nData8;						//Data8

    aBuffer[UDP_POS_CHECKSUM] = aBuffer[UDP_POS_ADDRESS] ^	//Checksum : XOR from Address to Data8
            aBuffer[UDP_POS_COMMAND] ^
            aBuffer[UDP_POS_DATA1] ^
            aBuffer[UDP_POS_DATA2] ^
            aBuffer[UDP_POS_DATA3] ^
            aBuffer[UDP_POS_DATA4] ^
            aBuffer[UDP_POS_DATA5] ^
            aBuffer[UDP_POS_DATA6] ^
            aBuffer[UDP_POS_DATA7] ^
            aBuffer[UDP_POS_DATA8];

    aBuffer[UDP_POS_TAIL] = UDP_PACKET_TAIL;				//Tail Byte : Fixed


    if(m_GenUdpClient)
    {
        m_GenUdpClient->writeDatagram((const char *)aBuffer,UDP_PACKET_SIZE,QHostAddress("169.254.1.4"),6000);
        return true;
    }

    return false;
}

