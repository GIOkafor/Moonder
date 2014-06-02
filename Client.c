#include <stdio.h>
#include <stdlib.h>
#include <sys/msg.h>
#include <string.h>

    struct my_msgbuf{
    int mtype;
    char mtext[200];
    };

    void main()
    {
    char inname[20];
    FILE *infile;
    char line_buffer[BUFSIZ];
    /* BUFSIZ is defined if you include stdio.h */
    int msqid, clmsqid, len;
    key_t key;
    struct my_msgbuf buf;

    //create client mq
    if((key=ftok("MoonderServer.c", 'M')) == -1){
        perror("ftok");
        exit(1);
    }

    if ((clmsqid = msgget(key, 0666 | IPC_CREAT)) == -1) {
        perror("msgget failed to create client mq");
        exit(1);
    }
    //end creation of client mq

    //join Server message queue with static key
    if((msqid = msgget((key_t)120, 0666)) != -1){
        printf("Joined queue with id:%d\n",msqid);
        //send message to message queue created by server the msgqid of created mqueue
       // sprintf(buf.mtext,"%d",clmsqid);//set message to be sent to server to be client message queue Id

       strcpy(buf.mtext,"hello world");//test to see if send works
        buf.mtype = 1;
        len = strlen(buf.mtext);
        /* ditch newline at end, if it exists */
        if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';

    if((msgsnd(msqid,&buf, len+1, 0) == -1)){
        perror("msgsnd of clmsqid to server queue failed");
        exit(1);
       }
       //end send
        printf("Sent message:%s \n",buf.mtext);
    }
    else{
        perror("msgget failed to join server");
        exit(1);
    }


    printf("Enter name of file with format specified : ");
    scanf("%s", inname);

    strcpy(buf.mtext, inname);//set second message to be sent to be name of file
    len = strlen(buf.mtext);

        if (buf.mtext[len-1] == '\n') buf.mtext[len-1] = '\0';
    //send filename to message queue
    if((msgsnd(msqid,&buf, len+1, 0) == -1)){
        perror("msgsnd");
        exit(1);
       }
       //end send of file name
        printf("Sent message:%s \n",buf.mtext);

        //blocks until messaged is received
       //receive acknowledgement msg from server on private msgqueue
     if((msgrcv(clmsqid, &buf, sizeof(buf.mtext), 0, 0)) == -1){
        perror("msgrcv");
        exit(1);
    }
    //end receive

    }
