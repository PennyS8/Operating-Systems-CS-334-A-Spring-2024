
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

void close_pipe(int pipefd [2]);

int main(void) {

  int pipefd[2];
  int pid;

  if (pipe(pipefd) < 0) {  //open pipe
    fprintf(stderr,"pipe failed");
  }
  if ((pid = fork()) < 0) { // create child
    fprintf(stderr,"fork failed");
  }

  if (pid == 0) {
    if (dup2(pipefd[1], STDOUT_FILENO) == -1) {
      fprintf(stderr,"dup2");
    } 

    if((close(pipefd[0]) < 0 ) || (close(pipefd[1]) < 0 )){
      perror("close");
      exit(EXIT_FAILURE);
    }
    
    char** args = malloc(sizeof (char*)*3);
    args[0] = strdup("cat");
    args[1] = strdup("Lab4Part3.c");
    args[2] = NULL;

    execvp(args[0], args);
    
    perror("execvp");
    for (int i = 0; i < 3; ++i) 
      free(args[i]);
    free(args);
    exit(EXIT_FAILURE);

    } 
  
  if ((pid = fork()) == -1) { 
    fprintf(stderr,"fork");
  }

  if (pid == 0) {
    if (dup2(pipefd[0], STDIN_FILENO) == -1) {
      fprintf(stderr,"dup2");
    }

    if((close(pipefd[0]) < 0 ) || (close(pipefd[1]) < 0 )){
      perror("close");
      exit(EXIT_FAILURE);
    }
    char** args = malloc(sizeof (char*)*2);;
    args[0] = strdup("less");
    args[1] = NULL;

    execvp(args[0], args);
    
    perror("execvp");
    for (int i = 0; i < 2; ++i) 
      free(args[i]);
    free(args);
    exit(EXIT_FAILURE);

  }

  if((close(pipefd[0]) < 0 ) || (close(pipefd[1]) < 0 )){
    perror("close");
    exit(EXIT_FAILURE);
  }
  waitpid(pid, NULL, 0); 
  return EXIT_SUCCESS;
} 



