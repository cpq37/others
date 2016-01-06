
#include "Debug_Log.h"
#include "IPC_Message.h"


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>



/*****************************************************************************
 * *  Name        : IPC_MSG_Create
 * *  Description : Create Message channel
 * *  Parameter   : Channel index
 * *  Returns     : The ID of the message queue
 * ***************************************************************************/
int IPC_MSG_Create(int index)
{
    key_t key;
    int msgqid = -1;
    DEBUG_LINE();
    if( (key=ftok(MSG_FILE, index)) == -1 )
    {
        DEBUG_ERR("ftok Error:");
        return -1;
    }

    if( (msgqid=msgget(key, READ_AND_WRITE|IPC_CREAT/*|IPC_EXCL*/)) == -1 )
    {
        DEBUG_ERR("msgget Error:");
        return -1;
    }

    return msgqid;

}
/*
int IPC_MSG_Destroy(int qid)
{
    if(msgctl(qid,IPC_RMID,0) == -1)
    {
        DEBUG_ERR("msgctl(IPC_RMID) failed.");
        return -1;
    }
    else
    {
        //DEBUG_ERR("msgctl(IPC_RMID) success");
        return 0;
    }
}
*/
//static MSGBUF msg;

/*****************************************************************************
 * *  Name        : IPC_MSG_SendMessage
 * *  Description : Send Message to channel and wait
 * *  Parameter   : queue ID,message ID, parameter1, parameter2
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_SendMessage(int qId, int msgId, unsigned int wParam, unsigned int lParam)
{
    DEBUG_INFO("%d, %d, 0x%x, 0x%x",qId, msgId, wParam, lParam);    
    struct msgtype msg;
    struct Message msgParam;
    memset(&msg, 0x00, sizeof(msg));
    memset(&msgParam, 0x00, sizeof(msgParam));
    msgParam.msgID  = msgId;
    msgParam.wParam = wParam;
    msgParam.lParam = lParam;
    memcpy(&msg, &msgParam, sizeof(msg));

    if (0 > msgsnd(qId, (const void*)&msg, sizeof(struct msgtype)-sizeof(long), 0) )
    {
        DEBUG_ERR("msgsnd failed!");
        return -1;
    }
    else    
        return 0;
}

/*****************************************************************************
 * *  Name        : IPC_MSG_PostMessage
 * *  Description : Send Message to channel,not wait
 * *  Parameter   : queue ID,message ID, parameter1, parameter2
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_PostMessage(int qId, int msgId, unsigned int wParam, unsigned int lParam)
{
    DEBUG_INFO("%d, %d, 0x%x, %u",qId, msgId, wParam, lParam);    
    struct msgtype msg;
    struct Message msgParam;
    memset(&msg, 0x00, sizeof(msg));
    memset(&msgParam, 0x00, sizeof(msgParam));
    msgParam.msgID  = msgId;
    msgParam.wParam = wParam;
    msgParam.lParam = lParam;
    memcpy(&msg, &msgParam, sizeof(msg));

    if ( 0 > msgsnd(qId, (const void*)&msg, sizeof(struct msgtype)-sizeof(long), IPC_NOWAIT) )
    {
        DEBUG_ERR("msgsnd failed!");
        return -1;
    }
    else
        return 0;

}

/*****************************************************************************
 * *  Name        : IPC_MSG_PeekMessage
 * *  Description : Get Message from channel,not wait
 * *  Parameter   : queue ID,message ID, message parameter
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_PeekMessage(int qId, int msgId, MESSAGE* const pMsg)
{
    struct msgtype msg;    
    memset(&msg, 0x00, sizeof(msg));
    if ( 0 > msgrcv(qId, &msg, sizeof(struct msgtype), msgId, IPC_NOWAIT) )
    {
        DEBUG_ERR("msgrcv failed!");
        return -1;
    }
    else
    {
        pMsg->msgID = msg.mtype;
        pMsg->wParam = 0;
        pMsg->wParam += (msg.buffer[0]&0x000000ff);
        pMsg->wParam += (msg.buffer[1]&0x000000ff)<<8;
        pMsg->wParam += (msg.buffer[2]&0x000000ff)<<16;
        pMsg->wParam += (msg.buffer[3]&0x000000ff)<<24;
        pMsg->lParam = 0;
        pMsg->lParam += (msg.buffer[4]&0x000000ff);
        pMsg->lParam += (msg.buffer[5]&0x000000ff)<<8;
        pMsg->lParam += (msg.buffer[6]&0x000000ff)<<16;
        pMsg->lParam += (msg.buffer[7]&0x000000ff)<<24; 

        DEBUG_INFO("Error:%s,Receive: %d, %x, %x", strerror(errno), pMsg->msgID, pMsg->wParam, pMsg->lParam);
    }

    return 0;
}

/*****************************************************************************
 * *  Name        : IPC_MSG_WaitMessage
 * *  Description : Wait Message from channel
 * *  Parameter   : queue ID,message ID, message parameters
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_WaitMessage(int qId, MESSAGE* const pMsg, int msgId)
{
    struct msgtype msg;    
    memset(&msg, 0x00, sizeof(msg));
    if ( 0 > msgrcv(qId, &msg, sizeof(struct msgtype)-sizeof(long), msgId, 0) )
    {
        DEBUG_ERR("msgrcv failed!");
        return -1;
    }
    else
    {
        pMsg->msgID = msg.mtype;
        pMsg->wParam = 0;
        pMsg->wParam += (msg.buffer[0]&0x000000ff);
        pMsg->wParam += (msg.buffer[1]&0x000000ff)<<8;
        pMsg->wParam += (msg.buffer[2]&0x000000ff)<<16;
        pMsg->wParam += (msg.buffer[3]&0x000000ff)<<24;
        pMsg->lParam = 0;
        pMsg->lParam += (msg.buffer[4]&0x000000ff);
        pMsg->lParam += (msg.buffer[5]&0x000000ff)<<8;
        pMsg->lParam += (msg.buffer[6]&0x000000ff)<<16;
        pMsg->lParam += (msg.buffer[7]&0x000000ff)<<24; 

        DEBUG_INFO("Receive: %d, %x, %x", pMsg->msgID, pMsg->wParam, pMsg->lParam);
    }
    return 0;
}

/*****************************************************************************
 * *  Name        : IPC_MSG_WaitMessageBuffer
 * *  Description : Wait Message from channel
 * *  Parameter   : queue ID, message buffer, message ID
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_WaitMessageBuffer(int qId, void* pMsg, int msgSize)
{
    struct msgtype msg;
    memset(&msg, 0, sizeof(msg));
    if( 0 > msgrcv(qId, &msg, sizeof(struct msgtype)-sizeof(long), 0, MSG_NOERROR) )
    {
        DEBUG_ERR("msgrcv failed!");
        return -1;
    }
    else
    {
        if( pMsg )
        {
            memcpy(pMsg, msg.buffer, msgSize); 
            //DEBUG_INFO("%d", msg.mtype);
            return msg.mtype;
        }
        else
        {
            DEBUG_ERR("parament is not valid!");
            return -1;
        }
    }
    return 0;
}

/*****************************************************************************
 * *  Name        : IPC_MSG_PeekMessageBuffer
 * *  Description : Get Message from channel,not wait
 * *  Parameter   : queue ID,message ID, message parameters
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_PeekMessageBuffer(int qId, void* pMsg, int msgSize)
{
    struct msgtype msg;
    memset(&msg, 0, sizeof(msg));
    if( 0 > msgrcv(qId, &msg, sizeof(struct msgtype)-sizeof(long), 0, IPC_NOWAIT) )
    {
        if( errno != 42 )
            DEBUG_ERR("msgrcv failed!");
        return -1;
    }
    else
    {
        if( pMsg )
        {
            memcpy(pMsg, msg.buffer, msgSize); 
            //DEBUG_INFO("%d", msg.mtype);
            return msg.mtype;
        }
        else
        {
            DEBUG_ERR("parament is not valid!");
            return -1;
        }
    }
    return 0;
}

/*****************************************************************************
 * *  Name        : IPC_MSG_SendMessageBuffer
 * *  Description : Send Message buffer to channel
 * *  Parameter   : queue ID,message ID, buffer size, message buffer
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_SendMessageBuffer(int qId, int msgId, unsigned bufferSize, char* buffer)
{
    //DEBUG_INFO("%d, %d, 0x%x, 0x%x\n",qId, msgId, bufferSize, buffer);    
    struct msgtype msg;
    memset(&msg, 0x00, sizeof(msg));
    msg.mtype = msgId;
    memcpy(msg.buffer, buffer, sizeof(msg.buffer));

    if (0 > msgsnd(qId, (const void*)&msg, sizeof(struct msgtype)-sizeof(long), MSG_NOERROR) )
    {
        DEBUG_ERR("msgsnd failed!");
        return -1;
    }
    else 
        return 0;
}
