#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

int main(void){
    pid_t dpid = getpid();

    printf("SSS %d \n", (int)dpid);

    if(kill(dpid, SIGABRT) == -1){
        fprintf(stderr, "Cannot send signal\n");
        return -1;
    }

    return 0;

}