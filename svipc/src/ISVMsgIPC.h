
#ifndef HEAD_ISVPMsgIPC
#define HEAD_ISVPMsgIPC



#include "SVP_IPC.h"

namespace SVP_IPC
{

//typedef int MsgQueueId;


class ISVPMsgIPC : public SVPMsgIPC
{
public:
    ISVPMsgIPC(void);
    virtual ~ISVPMsgIPC(void);

/*****************************************************************************
 * *  Name        : CreateMsgChannel
 * *  Description : Create Message channel
 * *  Parameter   : Channel index
 * *  Returns     : The ID of the message queue
 * ***************************************************************************/
    MsgQueueId CreateMsgChannel(int nChannel=0);
    
/*****************************************************************************
 * *  Name        : SendMessage
 * *  Description : Send Message to channel and wait
 * *  Parameter   : message ID, parameter1, parameter2, queue ID
 * *  Returns     : Success or Failure
 * ***************************************************************************/
    bool SendMessage(int msgId, long wParam, long lParam, MsgQueueId qId = 0);

/*****************************************************************************
 * *  Name        : SVSendMessage
 * *  Description : Send Message buffer to channel
 * *  Parameter   : message ID, buffer size, message buffer, queue ID
 * *  Returns     : Success or Failure
 * ***************************************************************************/
    bool SendMessage(int msgId, char* buffer, long bufferSize, MsgQueueId qId = 0);

/*****************************************************************************
 * *  Name        : SVGetMessage
 * *  Description : Get Message from buffer to long parameter,
 * used in the OnMessageHandler()
 * *  Parameter   : message buffer, parameter1, parameter2
 * *  Returns     : Success or Failure
 * ***************************************************************************/
    bool GetMessage(const char* buffer, long& wParam, long& lParam);


    virtual void OnMessageHandler(int msgId, const char* buffer) = 0;

};

}
#endif //HEAD_ISVPMsgIPC
