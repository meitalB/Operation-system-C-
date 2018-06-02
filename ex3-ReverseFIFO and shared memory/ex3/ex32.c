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
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <printf.h>
#define SHM_SIZE 4096
key_t key;
int board[64];
//int  (*array)[1];
int shmid;
char* shm;
struct shmid_ds ds;
char idOfPlayer;
int numOfMyPlayer;//b=1 w=2
char  myLastMessage[4];

/************************************************************************
 name function: printBoard
The Input:no input
The output : no output
The function operation:print the board to screen
 *************************************************************************/
void printBoard(){
    printf("The board is:\n");
    int i;
    for( i=0; i<64; i++){
        if(i%8==0){
            printf("\n");
        }
        printf("%d ",board[i]);

    }
    printf("\n");
    printf("\n");
}


/************************************************************************
 name function: check_right
The Input:point x,y, the num of the current player
The output : return 1  If there are coins that can be turned otherwise 0
The function operation:calculate if there is coins we can turned
 *************************************************************************/
int check_right(int x, int y,int numOfcurrentPlayer) {
    int i;
    if ((x + y * 8 + 1 >= 0) && (x + y * 8 + 1 <= 63)) {
        if ((board[x + y * 8 + 1] != numOfcurrentPlayer)
            && (board[x + y * 8 + 1] != 0)) {
            for ( i = x + y * 8 + 1; i <= y * 8 + 7; i++) {
                if (board[i] == 0) {
                    break;
                }
                if (board[i] == numOfcurrentPlayer) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
/************************************************************************
 name function: check_left
The Input:point x,y, the num of the current player
The output : return 1  If there are coins that can be turned otherwise 0
The function operation:calculate if there is coins we can turned
 *************************************************************************/
int check_left(int x,int y,int numOfcurrentPlayer) {
    int i;
    if ((x + y * 8 - 1 >= 0) && (x + y * 8 - 1 <= 63)) {
        if ((board[x + y * 8 - 1] != numOfcurrentPlayer)
            && (board[x + y * 8 - 1] != 0)) {
            for ( i = x + y * 8 - 1; i >= y * 8; i--) {

                if (board[i] == 0) {
                    break;
                }
                if (board[i] == numOfcurrentPlayer) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
/************************************************************************
 name function: check_down
The Input:point x,y, the num of the current player
The output : return 1  If there are coins that can be turned otherwise 0
The function operation:calculate if there is coins we can turned
 *************************************************************************/
int check_down(int x,int y,int numOfcurrentPlayer) {
    int i;
    if ((x + y * 8 + 8 >= 0) && (x + y * 8 + 8 <= 63)) {
        if ((board[x + y * 8 + 8] != numOfcurrentPlayer)
            && (board[x + y * 8 + 8] != 0)) {
            for ( i = x + y * 8 + 8; i <= 63; i = i + 8) {
                if (board[i] == 0) {
                    break;
                }
                if (board[i] == numOfcurrentPlayer) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
/************************************************************************
 name function: check_up
The Input:point x,y, the num of the current player
The output : return 1  If there are coins that can be turned otherwise 0
The function operation:calculate if there is coins we can turned
 *************************************************************************/
int check_up(int x,int y, int numOfcurrentPlayer ){
    int i;
    if((x + y * 8 -8>=0)&&(x + y * 8 -8<=63)) {
        if ((board[x + y * 8 - 8] != numOfcurrentPlayer)
            && (board[x + y * 8 - 8] != 0)) {
            for ( i = x + y * 8 - 8; i >=0; i = i - 8) {
                if (board[i] == 0) {
                    break;
                }
                if (board[i] == numOfcurrentPlayer) {
                    return 1;
                }
            }
        }
    }
    return 0;
}
/************************************************************************
 name function: check_up_right
The Input:point x,y, the num of the current player
The output : return 1  If there are coins that can be turned otherwise 0
The function operation:calculate if there is coins we can turned
 *************************************************************************/
int check_up_right(int x,int y,int numOfcurrentPlayer) {
    int i;
    if (((x + y * 8 - 7) % 8 != 0) && (x + y * 8 - 7 >= 0)
        && (x + y * 8 - 7 <= 63)) {
        if ((board[x + y * 8 - 7] != numOfcurrentPlayer)
            && (board[x + y * 8 - 7] != 0)) {
            for ( i = x + y * 8 - 7; i >= 0; i = i - 7) {

                if (board[i] == 0) {
                    break;
                }
                if (board[i] == numOfcurrentPlayer) {
                    return 1;
                }
                if ((i - 7) % 8 == 0) {
                    break;
                }
            }
        }
    }
    return 0;
}
/************************************************************************
 name function: check_down_left
The Input:point x,y, the num of the current player
The output : return 1  If there are coins that can be turned otherwise 0
The function operation:calculate if there is coins we can turned
 *************************************************************************/
int check_down_left(int x, int y,int numOfcurrentPlayer){
    int i;
    if(((x+y*8+7)%8!=7)&&(x+y*8+7>=0)&&(x+y*8+7<=63)) {
        if ((board[x + y * 8 + 7] != numOfcurrentPlayer)
            && (board[x + y * 8 + 7] != 0)) {

            for ( i = x + y * 8 + 7; i <= 63; i = i + 7) {

                if (board[i] == 0) {
                    break;
                }
                if (board[i] == numOfcurrentPlayer) {
                    return 1;
                }
                if ((i + 7) % 8 == 7) {
                    break;
                }
            }
        }
    }
    return 0;
}
/************************************************************************
 name function: check_down_right
The Input:point x,y, the num of the current player
The output : return 1  If there are coins that can be turned otherwise 0
The function operation:calculate if there is coins we can turned
 *************************************************************************/
int check_down_right(int x, int y, int numOfcurrentPlayer){
    int i;
    if(((x+y*8+9)%8!=0)&&(x+y*8+9>=0)&&(x+y*8+9<=63)) {
        if ((board[x + y * 8 + 9] != numOfcurrentPlayer)
            && (board[x + y * 8 + 9] != 0)) {

            for ( i = x + y * 8 + 9; i <= 63; i = i + 9) {

                if (board[i] == 0) {
                    break;
                }
                if (board[i] == numOfcurrentPlayer) {
                    return 1;
                }
                if ((i + 9) % 8 == 0) {
                    break;
                }
            }
        }
    }
    return 0;
}
/************************************************************************
 name function: check_up_left
The Input:point x,y, the num of the current player
The output : return 1  If there are coins that can be turned otherwise 0
The function operation:calculate if there is coins we can turned
 *************************************************************************/
int check_up_left(int x, int y,int numOfcurrentPlayer) {
    int i;
    if (((x + y * 8 - 9) % 8 != 0) && (x + y * 8 - 9 >= 0)
        && (x + y * 8 - 9 <= 63)) {
        if ((board[x + y * 8 - 9] != numOfcurrentPlayer)
            && (board[x + y * 8 - 9] != 0)) {

            for ( i = x + y * 8 - 9; i >= 0; i = i - 9) {

                if (board[i] == 0) {
                    break;
                }
                if (board[i] == numOfcurrentPlayer) {
                    return 1;
                }
                if ((i - 9) % 8 == 7) {
                    break;
                }
            }
        }
    }
    return 0;
}
/************************************************************************
 name function: updateMyBoard
The Input:point x,y, the num of the current player
The output : no output
The function operation:update board due to before checks coins
 *************************************************************************/
void updateMyBoard(int x,int y,int numOfcurrentPlayer){
    int i;
    board[x+y*8]=numOfcurrentPlayer;
    //check right
    if(check_right(x,y,numOfcurrentPlayer)==1) {
        if ((x + y * 8 + 1 >= 0) && (x + y * 8 + 1 <= 63)) {
            if ((board[x + y * 8 + 1] != numOfcurrentPlayer)
                && (board[x + y * 8 + 1] != 0)) {
                for ( i = x + y * 8 + 1; i <= y * 8 + 7; i++) {
                    if (board[i] == 0) {
                        break;
                    }
                    if (board[i] ==numOfcurrentPlayer) {
                        break;
                    }
                    if (board[i] != numOfcurrentPlayer) {
                        board[i] = numOfcurrentPlayer;
                    }
                }
            }
        }
    }
    //check left
    if(check_left(x,y,numOfcurrentPlayer)==1) {
        int i;
        if ((x + y * 8 - 1 >= 0) && (x + y * 8 - 1 <= 63)) {
            if ((board[x + y * 8 - 1] != numOfcurrentPlayer)
                && (board[x + y * 8 - 1] != 0)) {
                for ( i = x + y * 8 - 1; i >= y * 8; i--) {
                    if (board[i] == 0) {
                        break;
                    }
                    if (board[i] ==numOfcurrentPlayer) {
                        break;
                    }
                    if (board[i] != numOfcurrentPlayer) {
                        board[i] = numOfcurrentPlayer;
                    }
                }
            }
        }
    }
    //check down
    if(check_down(x,y,numOfcurrentPlayer)==1) {
        int i;
        if ((x + y * 8 + 8 >= 0) && (x + y * 8 + 8 <= 63)) {
            if ((board[x + y * 8 + 8] != numOfcurrentPlayer)
                && (board[x + y * 8 + 8] != 0)) {
                for ( i = x + y * 8 + 8; i <= 63; i = i + 8) {
                    if (board[i] == 0) {
                        break;
                    }
                    if (board[i] ==numOfcurrentPlayer) {
                        break;
                    }
                    if (board[i] != numOfcurrentPlayer) {
                        board[i] = numOfcurrentPlayer;
                    }
                }
            }
        }
    }
    //check up
    if(check_up(x,y,numOfcurrentPlayer)==1) {
        int i;
        if ((x + y * 8 - 8 >= 0) && (x + y * 8 - 8 <= 63)) {
            if ((board[x + y * 8 - 8] != numOfcurrentPlayer)
                && (board[x + y * 8 - 8] != 0)) {
                for ( i = x + y * 8 - 8; i >= 0; i = i - 8) {
                    if (board[i] == 0) {
                        break;
                    }
                    if (board[i] ==numOfcurrentPlayer) {
                        break;
                    }
                    if (board[i] != numOfcurrentPlayer) {
                        board[i] = numOfcurrentPlayer;
                    }
                }
            }
        }
    }
    //check up-right
    if(check_up_right(x,y,numOfcurrentPlayer)==1) {
        int i;
        if (((x + y * 8 - 7) % 8 != 0) && (x + y * 8 - 7 >= 0)
            && (x + y * 8 - 7 <= 63)) {
            if ((board[x + y * 8 - 7] != numOfcurrentPlayer)
                && (board[x + y * 8 - 7] != 0)) {
                for ( i = x + y * 8 - 7; i >= 0; i = i - 7) {

                    if (board[i] == 0) {
                        break;
                    }
                    if (board[i] ==numOfcurrentPlayer) {
                        break;
                    }
                    if (board[i] != numOfcurrentPlayer) {
                        board[i] = numOfcurrentPlayer;
                    }
                    if ((i - 7) % 8 == 0) {
                        break;
                    }
                }
            }
        }
    }
    //check down-left
    if(check_down_left(x,y,numOfcurrentPlayer)==1) {
        int i;
        if (((x + y * 8 + 7) % 8 != 7) && (x + y * 8 + 7 >= 0)
            && (x + y * 8 + 7 <= 63)) {
            if ((board[x + y * 8 + 7] != numOfcurrentPlayer)
                && (board[x + y * 8 + 7] != 0)) {

                for ( i = x + y * 8 + 7; i <= 63; i = i + 7) {

                    if (board[i] == 0) {
                        break;
                    }
                    if (board[i] ==numOfcurrentPlayer) {
                        break;
                    }
                    if (board[i] != numOfcurrentPlayer) {
                        board[i] = numOfcurrentPlayer;
                    }
                    if ((i + 7) % 8 == 7) {
                        break;
                    }
                }
            }
        }
    }
    //check down-right
    if(check_down_right(x,y,numOfcurrentPlayer)==1) {
        int i;
        if (((x + y * 8 + 9) % 8 != 0) && (x + y * 8 + 9 >= 0)
            && (x + y * 8 + 9 <= 63)) {
            if ((board[x + y * 8 + 9] != numOfcurrentPlayer)
                && (board[x + y * 8 + 9] != 0)) {

                for ( i = x + y * 8 + 9; i <= 63; i = i + 9) {

                    if (board[i] == 0) {
                        break;
                    }
                    if (board[i] ==numOfcurrentPlayer) {
                        break;
                    }
                    if (board[i] != numOfcurrentPlayer) {
                        board[i] = numOfcurrentPlayer;
                    }
                    if ((i + 9) % 8 == 0) {
                        break;
                    }
                }
            }
        }
    }
    //check up-left
    if(check_up_left(x,y,numOfcurrentPlayer)==1) {
        int i;
        if (((x + y * 8 - 9) % 8 != 0) && (x + y * 8 - 9 >= 0)
            && (x + y * 8 - 9 <= 63)) {
            if ((board[x + y * 8 - 9] != numOfcurrentPlayer)
                && (board[x + y * 8 - 9] != 0)) {

                for ( i = x + y * 8 - 9; i >=0; i = i - 9) {

                    if (board[i] == 0) {
                        break;
                    }
                    if (board[i] ==numOfcurrentPlayer) {
                        break;
                    }
                    if (board[i] != numOfcurrentPlayer) {
                        board[i] = numOfcurrentPlayer;
                    }
                    if ((i - 9) % 8 == 7) {
                        break;
                    }
                }
            }
        }
    }

}
/************************************************************************
 name function: readLastBoard
The Input:no input
The output : no output
The function operation:read Last Board
 *************************************************************************/
void readLastBoard(){
    char ch;
    if(numOfMyPlayer==1){
        ch='w';
    }else{
        ch='b';
    }
    int x = shm[1] - '0';
    int y = shm[2] - '0';
    if(numOfMyPlayer==1){
        updateMyBoard(x,y,2);
    }else{
        updateMyBoard(x,y,1);
    }
}
/************************************************************************
 name function: init board
The Input:no input
The output : no output
The function operation:init with 0 board
 *************************************************************************/
void initBoard(){
    int i;
    for( i=0; i<64; i++){
        board[i]=0;

    }

    board[27]=1;
    board[28]=2;
    board[35]=2;
    board[36]=1;

    if(idOfPlayer == 'w'){
        readLastBoard();
    }

}
/************************************************************************
 name function: checkSquareChangeSomething
The Input:x,y, the num of the current player
The output :1 if there is coins to turned
The function operation:check if there reason to continue
 *************************************************************************/
int checkSquareChangeSomething(int x, int y, int currentPlayer)
{//1 good 0 not found
    if ((check_right(x, y,currentPlayer) == 1)||
            (check_left(x,y,currentPlayer)==1)||
            (check_down(x,y,currentPlayer)==1)
            ||(check_up(x,y,currentPlayer)==1)||
            (check_up_right(x,y,currentPlayer)==1)
        ||(check_up_left(x,y,currentPlayer)==1)
    ||(check_down_left(x,y,currentPlayer)==1)||
            (check_down_right(x,y,currentPlayer)==1)){
        return 1;
    }
    return 0;
}
/************************************************************************
 name function: checkEmptySquare
The Input:str from input
The output : if the square empty1 otherwise0
The function operation::check if the square empty
 *************************************************************************/
int checkEmptySquare(char str[5]){//1 empty 0 full
    int x = str[1] - '0';
    int y = str[3] - '0';
    if(board[x+y*8]==0){
        return 1;
    }
    return 0;
}
/************************************************************************
 name function: checkInputStr
The Input:str from input
The output : if the str correct 1 otherwise0
The function operation::check if the str correct
 *************************************************************************/
int checkInputStr(char str[5]) {//1 right format, 0 worng format
    //check format
    int x = str[1] - '0';
    int y = str[3] - '0';
    if ((str[0] == '[') && ((x >= 0) && (x <= 7)) &&
            (str[2] == ',') && ((y >= 0) && (y <= 7))
        && (str[4] == ']')) {
        return 1;
    }
    return 0;
}
/************************************************************************
 name function: fullBoard
The Input:no input
The output : if the full Board 1 otherwise0
The function operation::check if the fullBoard
 *************************************************************************/
int fullBoard(){//0 not full, 1 full
    int i;
    for( i=0; i<64; i++){
        if(board[i]==0){
            return 0;
        }
    }
    return 1;
}
/************************************************************************
 name function: thereIsLagalStep
The Input:numPlayer
The output : if there Is Lagal Step 1 otherwise0
The function operation::check if the there Is Lagal Step
 *************************************************************************/
int thereIsLagalStep(int numPlayer){//1 there is, 0 there is no
    int x,y;
    for( x=0; x<8; x++){
        for( y=0; y<8; y++){
            if( (board[x+y*8]==0)
                &&(checkSquareChangeSomething(x,y,numPlayer)==1)){
                return 1;
            }
        }
    }
    return 0;
}
/************************************************************************
 name function: checkFinishGame
The Input:numPlayer
The output : if  Finish Game 1 otherwise0
The function operation::check Finish Game
 *************************************************************************/
int checkFinishGame(int numPlayer) {//1 not finish, 0 finish
    if (fullBoard() == 1) {
        return 0;
    }
    if (thereIsLagalStep(numPlayer) == 1) {
        return 1;
    }
    return 0;
}
/************************************************************************
 name function: firstWin
The Input:no input
The output : no
The function operation::print Finish Game
 *************************************************************************/
void firstWin(){
    int countWhite=0;
    int countBlack=0;
    int i;
    for( i=0; i<64; i++){
        if(board[i]==1){
            countWhite++;
        }else if(board[i]==2){
            countBlack;
        }
    }
    if(countBlack==countWhite){
        printf("No winning player\n");
    }else if(countBlack<countWhite) {
        printf("Winning player: White\n");
    } else{
        printf("Winning player: Black\n");
    }

}
/************************************************************************
 name function: chooseSquare
The Input:no input
The output : no
The function operation::check the choose Square
 *************************************************************************/
void chooseSquare(){
    if(checkFinishGame(numOfMyPlayer)==1) {

        char str[5];
        printf("Please choose a square\n");
        scanf("%s", str);
        int x = str[1] - '0';
        int y = str[3] - '0';
        while ((checkInputStr(str) == 0) ||
                (checkEmptySquare(str) == 0) ||
               (checkSquareChangeSomething(x, y, numOfMyPlayer) == 0)) {
            if ((checkInputStr(str) == 0)) {
                printf("No such square\nPlease choose another square\n");
            }
            else if ((checkEmptySquare(str) == 0) ||
                (checkSquareChangeSomething(x, y, numOfMyPlayer) == 0)) {
                printf("This square is invalid\nPlease choose another"
                               " square\n");
            }


           // printf("Please choose a square");
            scanf("%s", str);
            x = str[1] - '0';
            y = str[3] - '0';
        }
        //printf("Entered Name: %s\n", str);

        updateMyBoard(x, y, numOfMyPlayer);
        printBoard();

        //printf("idOfPlayer: %c\n", idOfPlayer);
        printf("Waiting for the other player to make a move\n");
        char stringForSharedMemory[4];
        stringForSharedMemory[0] = idOfPlayer;
        stringForSharedMemory[1] = str[1];//x
        stringForSharedMemory[2] = str[3];//y
        stringForSharedMemory[3] = '\0';

        strcpy(shm, stringForSharedMemory);
        strcpy(myLastMessage, stringForSharedMemory);
    }else{
        strcpy(shm, "exit");
        firstWin();}
}
/************************************************************************
 name function: connectSharedMemory
The Input:no input
The output : no
The function operation::connect Shared Memory
 *************************************************************************/
void connectSharedMemory() {


    if ((key = ftok("ex31.c", 'k')) == -1) {//TODO for terminal
        //     if ((key = ftok("../ex31.c", 'k')) == -1) {
        perror("ftok");
        exit(1);
    }
//    printf("shared memory\n");
    /*
    * Connect the segment.
    */
    if ((shmid = shmget(key, SHM_SIZE, 0666)) < 0) {
        perror("shmget");
        exit(1);
    }
    /*
    * Now we attach the segment to our data space.
    */
    if ((shm = shmat(shmid, NULL, 0)) == (void *) -1) {
        perror("shmat");
        exit(1);
    }
short n;
/* get info: */
    if (shmctl(shmid, IPC_STAT, &ds) == -1) {
        perror("shmctl");
        exit(1);
    } else {
     n=ds.shm_nattch;

        if(strchr(shm,'b')!=NULL){
            idOfPlayer = 'w';
            numOfMyPlayer=2;
        }else{
            idOfPlayer = 'b';
            numOfMyPlayer=1;
        }
//        printf("finish connect shared memory!\n");
//        printf("idOfPlayer: %c\n", idOfPlayer);
//        printf("number of connect!%d!!!!\n", n);
    }

}

/************************************************************************
 name function: waitingForNewInput
The Input:no input
The output : no
The function operation:waitingForNewInput
 *************************************************************************/
void waitingForNewInput() {
    int f=0;
    while (fullBoard() == 0) {
        char ch;
        if (numOfMyPlayer == 1) {
            ch = 'w';
        } else {
            ch = 'b';
        }
        while (strchr(shm, ch) == NULL) {
            if(numOfMyPlayer==1){
                if (thereIsLagalStep(2) == 0) {
                    f=1;
                    break;
                }
            }
            if(numOfMyPlayer==2){
                if (thereIsLagalStep(1) == 0) {
                    f=1;
                    break;
                }
            }
            sleep(1);
            printf("Waiting for the other player to make a move\n");
        }
        if(f==1){
            break;
        }
        int x = shm[1] - '0';
        int y = shm[2] - '0';
        if (numOfMyPlayer == 1) {
            updateMyBoard(x, y, 2);
        } else {
            updateMyBoard(x, y, 1);

        }
        printBoard();
        if (checkFinishGame(numOfMyPlayer) == 0) {
            break;
        }
        chooseSquare();

    }
    firstWin();
}

/************************************************************************
 name function: my_handler
The Input:no input
The output : no
The function operation handler sigusr1
 *************************************************************************/
void my_handler(int signum) {
    if (signum == SIGUSR1) {
//        printf("Received SIGUSR1!\n");
        connectSharedMemory();
        initBoard();
        printBoard();
        if(strchr(shm,'e')!=NULL){
           firstWin();
        }
        chooseSquare();
        waitingForNewInput();
    }
}
/************************************************************************
 name function: main
The Input:no input
The output : no output
The function operation:main server
 *************************************************************************/
int main()
{

    int fd_read,fd_write;
    char buf[80];
    fd_write=open("fifo_clientTOserver",O_WRONLY);
    pid_t myPid=getpid();
    write(fd_write,&myPid,sizeof(myPid));

    signal(SIGUSR1, my_handler);
    pause();


    return 0;
}
