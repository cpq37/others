
#include "ISVMsgIPC.h"
#include <stdio.h>
#include <unistd.h>

class App : public SVP_IPC::ISVPMsgIPC
{
public:
    App(void){ id = CreateMsgChannel('a'); }
    ~App(void){}
    void run(){ 
        char msgStr[] = "this is a test!";
        while(1)
        {sleep(1); SendMessage(1, msgStr, sizeof(msgStr));} 
    }


    virtual void OnMessageHandler(int msgId, const char* buffer)
    {
        if( msgId > 0) 
            printf("Class Client receive:%d, %s\n", msgId, buffer);
    }

private:
    MsgQueueId id;
};

/*
int test(void)
{
    SVPMsgIPC testIPC;
    MsgQueueId id0 = testIPC.CreateMsgChannel('b');
    MsgQueueId id = testIPC.CreateMsgChannel('a');

    char msgStr[] = "this is a test!";
    printf("id:%d, msgStr:%s, id0:%d\n", id, msgStr, id0);
    while(1)
    {
    testIPC.SendMessage(1,msgStr, sizeof(msgStr)); 
    printf("send over\n");
    sleep(1);
    }
    printf("destory\n");
    return 0;
}
*/
int main(void)
{
    printf("test""%d\n", 1);
    App app;
    app.run();
    return 0;
}
