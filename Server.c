#include <sys/msg.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#define N 50

struct my_msgbuf{
    long mtype;//change to int type
    char mtext[200];
    };

struct clientsOn{
    int id;
    struct clientsOn *next;
    char profile[200];
    char status[1];
};
/*goes in client.c

struct clients{
    char name[25];
    char info[200];
    char status[9];
};

void *client(){
    //populates array of structs with info of other clients
    //should be able to add and remove clients for when they join and leave
    //clients should have status as well

    //creates an array of structs containing clients on server
    struct clients profiles[MAX_CLIENTS];
    int i, n;
    i = 0;
    n = clientsOn;
    while(i < )
};
*/

 void *clientProcess(void *ptr)
    {
    int cl_id;
    char num[50];
    struct clientsOn *thr;
    struct my_msgbuf *msg;
    thr = (struct clientsOn *)ptr;
    strcpy(msg->mtext, "Welcome to moonder");
    //send acknowledgement msg to client mqueue
    cl_id = thr->id ;

    if((msgsnd(cl_id,&msg,strlen(msg->mtext),0))==-1){
        perror("msgsnd");
        exit(1);
    }
}

int main()
{

    struct my_msgbuf buf;

    int m,msqid,clientMsqId;//client msgq id
    key_t key;
    char inname[30];
    char welcome[] = "Welcome to moonder";


    //create queue as soon as server starts
    if((msqid = msgget((key_t)120, 0666 | IPC_CREAT)) == -1){
        perror("msgget");
        exit(1);
    }

    printf("Created queue with id: %d\n",msqid);
    //receive msg about client clmqid has to keep running to detect multiple clients joining
    for(;;){
    if(msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0) == -1){
        /*spawn thread argument for thread contains message content
        which is client msgqid*/
        perror("msgrcv");
        exit(1);
    }//receives message clients idnum in it's own queue
     printf("message received: %s",buf.mtext);//test for receive

    //clientMsqId = strtol(buf.mtext, &end, 10);//message queue id of client

    if((msgrcv(msqid, &buf, sizeof(buf.mtext), 0, 0)) == -1){
        perror("msgrcv");
        exit(1);
    }//receives client filename

    strcpy(inname,buf.mtext);//store client filename


    }

}

