
#include <unistd.h>
#include "Debug_Log.h"
//#include "IPC_Message.h"
#include "SVP_IPC.h"

using namespace SVP_IPC;

MsgQueueId SVPMsgIPC::mQueueId = 0;
MSGBUF SVPMsgIPC::msg = {0};
std::map<int, MsgQueueId> SVPMsgIPC::g_mapMsgQueue;


SVPMsgIPC::SVPMsgIPC(void)
{
    mQueueId = 0;
    mThreadId = 0;
}

SVPMsgIPC::~SVPMsgIPC(void)
{
    this->SVDestroy();
}


/*****************************************************************************
 * *  Name        : SVCreateMsgChannel
 * *  Description : Create Message channel
 * *  Parameter   : Channel index
 * *  Returns     : The ID of the message queue
 * ***************************************************************************/
MsgQueueId SVPMsgIPC::SVCreateMsgChannel(int nChannel)
{

    mQueueId = IPC_MSG_Create(nChannel);
    std::pair<int, MsgQueueId> pairMsgId;
    pairMsgId.first = nChannel;
    pairMsgId.second = mQueueId;
    g_mapMsgQueue.insert(pairMsgId);

    if( mThreadId <= 0 ) 
    { 
        if( 0!= pthread_create(&mThreadId, NULL, MsgThreadProc, (void*)this) )
        {
            return -1;
        }
    }

    DEBUG_INFO("thread id:%ld, mQueueId:%d,%d\n", mThreadId, g_mapMsgQueue.size(), (int)pairMsgId.second);

    return mQueueId;
}


/*****************************************************************************
 * *  Name        : SVDestroy
 * *  Description : Destory thread and datas
 * *  Parameter   : None
 * *  Returns     : Success or failure
 * ***************************************************************************/
bool SVPMsgIPC::SVDestroy()
{
    if( 0 != pthread_cancel(mThreadId) )
    {
        DEBUG_ERR("Cancel thread"); 
    }
    if( 0 != pthread_join(mThreadId,NULL) )
    {
        DEBUG_ERR("Join thread");
    }
    std::map<int, MsgQueueId>::iterator it = g_mapMsgQueue.begin();

    while( it != g_mapMsgQueue.end() )
    {
        if( (msg.mtype=IPC_MSG_PeekMessageBuffer(it->second, msg.buffer, sizeof(msg.buffer))) < 0 )
        {
        }
        else
        {
            OnMessageHandler(msg.mtype, msg.buffer);
        }
        g_mapMsgQueue.erase(it++);
    }

}


/*****************************************************************************
 * *  Name        : SVSendMessage
 * *  Description : Send Message to channel and wait
 * *  Parameter   : message ID, parameter1, parameter2, queue ID
 * *  Returns     : Success or Failure
 * ***************************************************************************/
bool SVPMsgIPC::SVSendMessage(int msgId, long wParam, long lParam, MsgQueueId qId)
{
    MsgQueueId tmpQueueId;
    if( 0 == qId )
    {
        tmpQueueId = mQueueId;
    }
    else
    {
        tmpQueueId = qId;
    }

    if( 0 > IPC_MSG_SendMessage(tmpQueueId, msgId, wParam, lParam) )
    {
        return false;
    }
    else
    {
        return true;
    }
}



/*****************************************************************************
 * *  Name        : SVSendMessage
 * *  Description : Send Message buffer to channel
 * *  Parameter   : message ID, buffer size, message buffer, queue ID
 * *  Returns     : Success or Failure
 * ***************************************************************************/
bool SVPMsgIPC::SVSendMessage(int msgId, char* buffer, long bufferSize, MsgQueueId qId)
{   
    MsgQueueId tmpQueueId;
    if( 0 == qId )
    {
        tmpQueueId = mQueueId;
    }
    else
    {
        tmpQueueId = qId;
    }

    if( 0 > IPC_MSG_SendMessageBuffer(tmpQueueId, msgId, bufferSize, buffer) )
    {
        return false;
    }
    else
    {
        return true;
    }
}

/*****************************************************************************
 * *  Name        : SVGetMessage
 * *  Description : Get Message from buffer to long parameter
 * *  Parameter   : message buffer, parameter1, parameter2
 * *  Returns     : Success or Failure
 * ***************************************************************************/
bool SVPMsgIPC::SVGetMessage(const char* buffer, long& wParam, long& lParam)
{
    if( buffer )
    {
        wParam = 0;
        lParam = 0;

        wParam += (buffer[0]&0x000000ff);
        wParam += (buffer[1]&0x000000ff)<<8;
        wParam += (buffer[2]&0x000000ff)<<16;
        wParam += (buffer[3]&0x000000ff)<<24;

        lParam += (buffer[4]&0x000000ff);
        lParam += (buffer[5]&0x000000ff)<<8;
        lParam += (buffer[6]&0x000000ff)<<16;
        lParam += (buffer[7]&0x000000ff)<<24; 

        return true;
    }
    else
        return false;
}

//void SVPMsgIPC::OnMessageHandler(int msgId, const char* buffer)
//{    
//    if( msgId > 0) 
//    printf("Class Client receive:%d, %s\n", msgId, buffer);
//}

/*****************************************************************************
 * *  Name        : MsgThreadProc
 * *  Description : Process the received message in the thread
 * *  Parameter   : Pointer(SVPMsgIPC object)
 * *  Returns     : None
 * ***************************************************************************/
void* SVPMsgIPC::MsgThreadProc(void* arg)
{
    //DEBUG_LINE();
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    while(1)
    {
        std::map<int, MsgQueueId>::iterator it = g_mapMsgQueue.begin();
        while( it != g_mapMsgQueue.end() )
        {
            //if( g_mapMsgQueue.size() > 1 )
            {
                usleep(100000);
                msg.mtype=IPC_MSG_PeekMessageBuffer(it->second, msg.buffer, sizeof(msg.buffer));
            }
            //else
            //{
            //    msg.mtype = IPC_MSG_WaitMessageBuffer( it->second, msg.buffer, sizeof(msg.buffer) );
            //}

            if( msg.mtype < 0 )
            {
            }
            else
            {
                SVPMsgIPC* ptr = (SVPMsgIPC*)arg;
                ptr->OnMessageHandler(msg.mtype, msg.buffer);
            }
            it++;
        }
    }
}

