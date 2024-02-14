#include <stdio.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>

#define BUFF_SIZE 128

int main(void) {

    pid_t pid1, pid2;
    int pipe_fd1 [2];
    int pipe_fd2 [2];

    printf("Before\n");

    // creating pipes
    if(pipe(pipe_fd1) == -1 || pipe(pipe_fd2) == -1){
        perror("Pipe error");
        exit(EXIT_FAILURE);
    }

    if ((pid1 = fork()) < 0){ // could not fork
        perror("FORK ERROR");
        exit(EXIT_FAILURE);
    }

    if (pid1 != 0) { // parent process
        if ((pid2 = fork()) < 0) {
        perror("FORK ERROR");
        exit(EXIT_FAILURE);
        }
        if (pid2 != 0) { // parent process
            char buff[BUFF_SIZE];
            printf("P:%d ch1:%d ch2:%d\n", getpid(), pid1, pid2);
            char msg_ch1[] = "cs334";
            char msg_ch2[] = "OS";

            // close parent's unused fd's
            close(pipe_fd1[0]);
            close(pipe_fd2[0]);

            // writing messages to child processes
            write(pipe_fd1[1], msg_ch1, strlen(msg_ch1) + 1);
            write(pipe_fd2[1], msg_ch2, strlen(msg_ch2) + 1);

            // wait for children to finish
            wait(NULL);
            wait(NULL);

            // close parent's used file descriptors
            close(pipe_fd1[1]);
            close(pipe_fd2[1]);

        } else { // child2 process
            char buff[BUFF_SIZE];
            printf("CH2: %d\n", getpid());

            // close child's unused fd's
            close(pipe_fd1[0]);
            close(pipe_fd1[1]);
            close(pipe_fd2[0]);

            // Read message from parent
            read(pipe_fd2[0], buff, BUFF_SIZE);
            printf("Child 2 received: %s\n", buff);

            // Close child's used file descriptor
            close(pipe_fd2[0]);

            exit(EXIT_SUCCESS);
        }

    } else {
        char buff[BUFF_SIZE];
        printf("C1: %d\n", getpid());

        // close chlid;s unused fd's
        close(pipe_fd1[1]);
        close(pipe_fd1[0]);
        close(pipe_fd2[1]);

        // Read message from parent
        read(pipe_fd1[0], buff, BUFF_SIZE);
        printf("Child 1 received: %s\n", buff);

        // Close child's used file descriptor
        close(pipe_fd1[0]);

        exit(EXIT_SUCCESS);
    }

    return EXIT_SUCCESS;
}
