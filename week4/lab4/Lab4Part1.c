#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define BUFFER_SIZE 14

int main(int argc, char* argv []) {
    printf("in main\n");                
    int fd;                             
    char buffer[BUFFER_SIZE];

    if ((fd = open(argv[1], O_RDONLY)) == -1){
        perror("open");
        exit (EXIT_FAILURE);
    }
    int rc_read = read(fd, buffer, BUFFER_SIZE);
    printf("From fd read:\n%.*s\n", rc_read, buffer);
/**********************************************
 * insert your code here
**************************************************/

    int fd_backup = dup(fd);
    if(fd_backup == -1){
        perror("dup");
        exit(EXIT_FAILURE);
    }

    int rc_read_backup = read(fd_backup, buffer, BUFFER_SIZE);
    printf("From fd_backup read:\n%.*s\n", rc_read_backup, buffer);

    rc_read = read(fd, buffer, BUFFER_SIZE);
    printf("From fd read:\n%*s\n", rc_read, buffer);

}