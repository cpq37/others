
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

#include "IPC_Message.h"

int main(void)
{
    //struct Message msg;
    struct msgtype msg;
    int msg_qid = -1;
    
    msg_qid = IPC_MSG_Create('a');
    fprintf(stderr, "MSG_QID:%d Starting...\n", msg_qid);
    {
        char msgStr[] = "this is a test!";
        //IPC_MSG_SendMessage(msg_qid, 1, (U32)msgStr, (U32)msgStr);
        IPC_MSG_SendMessageBuffer(msg_qid, 1, sizeof(msgStr), msgStr);

        fprintf(stderr, "qid:%d, Client Send Error:%s\a\n", msg_qid, strerror(errno));

        //IPC_MSG_WaitMessage(msg_qid, &msg, 0);
        msg.mtype = IPC_MSG_WaitMessageBuffer(msg_qid, msg.buffer, sizeof(msg.buffer));
        fprintf(stderr, "Client receive:%d, %s\n", msg.mtype, msg.buffer);
    }

    //IPC_MSG_Destroy(msg_qid);
    printf("End.\n");
    
    exit(0);
}
