
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>

int main(void){

    int fd[2];
    int fd2[2];
    pipe(fd);
    pipe(fd2);

    if(fork()){
        close(fd[0]);
        close(fd2[1]);

        const char *msg = "Parent send mess";
        write(fd[1], msg, strlen(msg) + 1);

        char buffer[100];
        read(fd2[0], buffer, sizeof(buffer));
        printf("Message  %s\n", buffer);

        close(fd2[0]);
        close(fd[1]);
    }else{
        close(fd[1]);
        close(fd2[0]);

        char buffer[100];
        read(fd[0], buffer, sizeof(buffer));

        const char *msg2 = "Children send mess";
        write(fd2[1], msg2, strlen(msg2) + 1);

        close(fd[0]);
        printf("Message  %s\n", buffer);
        close(fd2[1]);
    }    


    return 0;
}
