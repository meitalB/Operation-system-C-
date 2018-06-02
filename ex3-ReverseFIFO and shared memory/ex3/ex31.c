/******************************************
* Student name: Meital Birka
* Student: 311124283
* Course Exercise Group: 03
* Exercise name: Exercise 3
******************************************/
#include <sys/param.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include<string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>

#define FIFONAME "fifo_clientTOserver"
#define SHM_SIZE 4096  /* make it a 4K shared memory segment */
/************************************************************************
 name function: main
The Input:no input
The output : no output
The function operation:main server
 *************************************************************************/
int main(int argc, char *argv[]) {
    key_t key;
    int shmid;
    int file;//fifo
    int fd_read;
    int numOfPidPass = 0;
    pid_t firstPid=getpid();
    pid_t secondPid=getpid();
    int bytesRead = 0;
   //int  (*array)[4];
char* shm;
/* make the key: */
    if ((key = ftok("ex31.c", 'k')) == -1) {
    //     if ((key = ftok("../ex31.c", 'k')) == -1) {
        perror("ftok");
        exit(1);
    }

    /*
    * Create the segment.
    */
    if ((shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    /*
    * Now we attach the segment to our data space.
    */
    if (( shm =shmat(shmid, NULL, 0)) == (char *) -1) {
        perror("shmat");
        exit(1);
    }

/*make fifo*/
    file = mkfifo(FIFONAME, 0666);
    if (file < 0) {
        printf("Unable to create a fifo");
        exit(-1);
    }
    //wait for 2 pid pass
    fd_read = open(FIFONAME, O_RDONLY);
    if(fd_read<0) {
        printf("Unable to open file");
        exit(-1);
    }
//    printf("opened the FIFO for read\n");

    pid_t choice;
    while (numOfPidPass < 2) {
        bytesRead = (int) read(fd_read, &choice, sizeof(pid_t));
        if (bytesRead > 0) {
            if (numOfPidPass == 0) {//first
                firstPid = choice;
//                printf("one pid is read %d\n",firstPid);
                bytesRead = 0;
            }
            if (numOfPidPass == 1) {
                secondPid = choice;
//                printf("sec pid is read%d\n",secondPid);
            }
            numOfPidPass++;
            bytesRead = 0;
        }
    }
    close(fd_read);
    //delete the pipe from the system
    unlink(FIFONAME);
//pid_t child_pid;
//   int ended;
//    if ((child_pid = fork()) == 0) {
        int ret;
        ret = kill(firstPid, SIGUSR1);

    strcpy(shm,"jjj");
       while (strcmp(shm,"jjj")==0){
           sleep(1);
          // printf("still waiting\n");

       }
    int ret2;
    ret2 = kill(secondPid, SIGUSR1);

   sleep(5);

    /* remove it: */
    if (shmctl(shmid, IPC_RMID, NULL) == -1) {
        perror("shmctl");
        exit(1);
    }
    return 0;
}