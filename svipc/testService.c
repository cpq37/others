
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <errno.h>

/*
struct Message
{
    unsigned int msgID;
    unsigned int wParam;
    unsigned int lParam;
};*/
struct Message
{
    long mtype;
    char buffer[256];
};

static int myCount = 2;
int main(void)
{
    struct Message msg;
    key_t key;
    int msgid;

    printf("hello world!\n");
    if( (key=ftok("/bin", 'a')) == -1 )
    {
        fprintf(stderr, "ftok Error:%s\a\n", strerror(errno ));
        return -1;
    }

    if( (msgid=msgget(key, 0666|IPC_CREAT/*|IPC_EXCL*/)) == -1 )
    {
        fprintf(stderr, "msgget: Error:%s\a\n", strerror(errno ));
        return -1;
    }

    fprintf(stderr, "Starting...\n");
    while(1)
    {

        if( msgrcv(msgid, &msg, sizeof(struct Message)-sizeof(long), 1, 0) < 0 )
        {
            fprintf(stderr, "msgrcv Error:%s\a\n", strerror(errno)); 
            usleep(100000);
        }
        else
        {
            fprintf(stderr, "qid:%d, Server Send Error0:%s\a\n", msgid, strerror(errno));

            //msgrcv(msgid, &msg, sizeof(struct Message), 1, MSG_NOERROR);
            fprintf(stderr, "Server Receive:%d\n", msg.mtype);
            fprintf(stderr, "Server Receive Buffer:0x%x, 0x%x, 0x%x, 0x%x,0x%x\n", \
                    msg.buffer[0], msg.buffer[1], msg.buffer[2], msg.buffer[3], msg.buffer[4]);
            //long wParam = *(msg.buffer);
            //fprintf(stderr, "Server Receive param: %d\n", wParam);
            //fprintf(stderr, "Server Receive:%d, %s\n",msg.mtype,  msg.buffer);
            //fprintf(stderr, "Error:%s,Receive: %d, %d, %d\n", strerror(errno), msg.msgID, msg.wParam, msg.lParam);
            //msg.wParam++;
            usleep(100000);
            msg.mtype = myCount++; 
fprintf(stderr, "Server Receive Buffer:0x%x, 0x%x, 0x%x, 0x%x,0x%x\n", \
                    msg.buffer[0], msg.buffer[1], msg.buffer[2], msg.buffer[3], msg.buffer[4]);
            
            msgsnd(msgid, &msg, sizeof(struct Message)-sizeof(long), 0);
            fprintf(stderr, "qid:%d, Server Send Error:%s\a\n", msgid, strerror(errno));
        }
    }
    printf("End.\n");
    
    exit(0);
}
