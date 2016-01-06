
#include "ISVMsgIPC.h"

using namespace SVP_IPC;


ISVPMsgIPC::ISVPMsgIPC(void)
{
}


ISVPMsgIPC::~ISVPMsgIPC(void)
{
}

MsgQueueId ISVPMsgIPC::CreateMsgChannel(int nChannel)
{
    return SVCreateMsgChannel(nChannel);
}

bool ISVPMsgIPC::SendMessage(int msgId, long wParam, long lParam, MsgQueueId qId)
{
    return SVSendMessage(msgId, wParam, lParam, qId);
}

bool ISVPMsgIPC::SendMessage(int msgId, char* buffer, long bufferSize, MsgQueueId qId)
{
    return SVSendMessage(msgId, buffer, bufferSize, qId);
}

bool ISVPMsgIPC::GetMessage(const char* buffer, long& wParam, long& lParam)
{
    return SVGetMessage(buffer, wParam, lParam);
}



