
#ifndef HEAD_SVPMsgIPC
#define HEAD_SVPMsgIPC

#include <map>
#include <pthread.h>
#include "IPC_Message.h"

typedef int MsgQueueId;


namespace SVP_IPC
{
class SVPMsgIPC
{
public:
    SVPMsgIPC(void);
    virtual ~SVPMsgIPC(void);
    MsgQueueId SVCreateMsgChannel(int nChannel=0);
    bool SVDestroy();
    bool SVSendMessage(int msgId, long wParam, long lParam, MsgQueueId qId = 0);
    bool SVSendMessage(int msgId, char* buffer, long bufferSize, MsgQueueId qId = 0);
    // used in the OnMessageHandler()
    bool SVGetMessage(const char* buffer, long& wParam, long& lParam);
    virtual void OnMessageHandler(int msgId, const char* buffer) = 0;

protected:
    static void* MsgThreadProc(void* arg);
    static MsgQueueId mQueueId;
    static MSGBUF msg;
    static std::map<int,MsgQueueId> g_mapMsgQueue; 

private:
    pthread_t mThreadId;
};

}
#endif //HEAD_SVPMsgIPC
