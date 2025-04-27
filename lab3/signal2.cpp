#include <signal.h>
#include <stdio.h>


sig_atomic_t sig_occured = 0;
sig_atomic_t running = 1;

void sig_handler(int snum){
    sig_occured = 1;
}

void sigterm_handler(){
    running = 0;
}


int main(void){
    struct sigaction act;
    sigemptyset(&act.sa_mask);

    struct sigaction act_sigterm;
    sigemptyset(&act_sigterm.sa_mask);

    act.sa_handler = &sig_handler;
    act.sa_flags = 0;

    act_sigterm.sa_handler = &sig_handler;
    act_sigterm.sa_flags = 0;

    if(sigaction(SIGINT, &act, NULL) == -1){
        fprintf(stderr, "sigaction error SIGINT\n");
    }  

    if(sigaction(SIGTERM, &act, NULL) == -1){
        fprintf(stderr, "sigaction error SIGTERM\n");
    }   

    while(running){
        if(sig_occured){
            fprintf(stderr, "\nsignal....\n");
            sig_occured = 0;

        }
        printf("Running...\n");
        usleep(100000);
    }

    printf("Exiting program...\n");
    return 0;
}