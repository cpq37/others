#ifndef HEADER_IPC_MESSAGE_H
#define HEADER_IPC_MESSAGE_H

#if defined(__cplusplus)
extern "C" {
#endif


//#include "CommonType.h"
//#include "Debug_Log.h"

#define MSG_FILE        "/bin"
#define BUFFER          256
#define READ_AND_WRITE  0666


typedef struct Message 
{
    unsigned int msgID;
    unsigned int wParam;
    unsigned lParam;
} MESSAGE;

typedef struct msgtype 
{
    unsigned int mtype;
    char buffer[BUFFER];
} MSGBUF;

typedef enum
{
    MSG_DEFAULT_CHANNEL = 0,
    MSG_MAX_CHANNEL = 255
} MSG_CHANNELS;



/*****************************************************************************
 * *  Name        : IPC_MSG_Create
 * *  Description : Create Message channel
 * *  Parameter   : Channel index
 * *  Returns     : The ID of the message queue
 * ***************************************************************************/
int IPC_MSG_Create(int index);


/*****************************************************************************
 * *  Name        : IPC_MSG_SendMessage
 * *  Description : Send Message to channel and wait
 * *  Parameter   : queue ID,message ID, parameter1, parameter2
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_SendMessage(int qId, int msgId, unsigned int wParam, unsigned int lParam);


/*****************************************************************************
 * *  Name        : IPC_MSG_PostMessage
 * *  Description : Send Message to channel,not wait
 * *  Parameter   : queue ID,message ID, parameter1, parameter2
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_PostMessage(int qId, int msgId, unsigned int wParam, unsigned int lParam);

/*****************************************************************************
 * *  Name        : IPC_MSG_SendMessageBuffer
 * *  Description : Send Message buffer to channel
 * *  Parameter   : queue ID,message ID, buffer size, message buffer
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_SendMessageBuffer(int qId, int msgId, unsigned int bufferSize, char* buffer);


/*****************************************************************************
 * *  Name        : IPC_MSG_PeekMessage
 * *  Description : Get Message from channel,not wait
 * *  Parameter   : queue ID,message ID, message parameter
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_PeekMessage(int qId, int msgId, MESSAGE* const pMsg);


/*****************************************************************************
 * *  Name        : IPC_MSG_WaitMessage
 * *  Description : Wait Message from channel
 * *  Parameter   : queue ID,message ID, message parameters
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_WaitMessage(int qId, MESSAGE* const pMsg, int msgId);


/*****************************************************************************
 * *  Name        : IPC_MSG_WaitMessageBuffer
 * *  Description : Wait Message from channel
 * *  Parameter   : queue ID, message buffer, message ID
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_WaitMessageBuffer(int qId, void* pMsg, int msgSize);


/*****************************************************************************
 * *  Name        : IPC_MSG_PeekMessageBuffer
 * *  Description : Get Message from channel,not wait
 * *  Parameter   : queue ID,message ID, message parameters
 * *  Returns     : 0:Success; -1:Failure
 * ***************************************************************************/
int IPC_MSG_PeekMessageBuffer(int qId, void* pMsg, int msgSize);
#if defined(__cplusplus)
}
#endif


#endif /* HEADER_IPC_MESSAGE_H */





