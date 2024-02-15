#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>

#include "Lab5Part1.h"

#define KEY ftok("Lab5Part1.c", 65)
#define SIZE sizeof(sh_data)
#define RECORD_LEN 14

int main(void) {
  pid_t pid, cpid;
  int sh_id, fd, fd2, records;
  off_t bytes;
  pid = getpid();
 
  
  if((fd = open("scores.txt", O_RDONLY)) < 0){
    perror("open");
    exit(EXIT_FAILURE);
  }
  if((bytes = lseek(fd, 0, SEEK_END)) < 0){
    perror("lseek");
  }
  records = bytes / RECORD_LEN;
  printf("File size is: %ld\n", bytes);
  lseek(fd, -bytes, SEEK_CUR);
  if((fd2 = open("scores.txt", O_RDONLY)) < 0){
    perror("open");
    exit(EXIT_FAILURE);
  }
  lseek(fd2, (int)records/2 * RECORD_LEN, SEEK_SET);


  /****************************************
  * get shared memory and store the return value in sh_id
  * error check sh_id value for success
  */

  sh_data* g_data;
  /****************************************
  * attach the shared memory id to the process 
  * use g_data as a handle to the shared memory attached to the process
  * error g_data for success attaching memory to process
  */

  g_data->gpa = 0.0;            //initialize struct with initial values
  strcpy(g_data->name,"none");
  printf("A: Initial value: %s:%.1f\n", g_data->name, g_data->gpa);

  if((cpid = fork()) < 0){ //create and check child
    perror("Fork Error");
  }
  if(cpid == 0){
    printf("C: in child\n");
    sh_data* c_data;            // declare and set local variables
    char buffer[RECORD_LEN+1];
    char name[RECORD_LEN-3];
    int rc = 0;
    double l_gpa = 0;
    /****************************************
    * attach the shared memory id to the child process 
    * use c_data as a handle to the shared memory attached to the process
    * error c_data for success attaching memory to process
    */
    for(int i = 0; i < records/2+1; i++){
      if((rc = read(fd2, buffer, RECORD_LEN)) < 0){
        perror("c read"); 
        //clean up attached memory
        exit (EXIT_FAILURE);
      }
      sscanf(buffer, "%s %lf", name, &l_gpa);
      sleep(0.1);
      //printf("C: %s read: %s, gpa: %f\n", buffer, name, l_gpa);
      if(c_data->gpa < l_gpa){
        /****************
        * update the struct's slots name and GPA as you found a higher GPA
        *****************/
        printf("C: found higher GPA %s: %.1f\n", c_data->name, c_data->gpa);
      }
    }    
    /******************
    * detach the c_data handle from the process
    *******************/
    }else{
    printf("P: in parent\n");
    int rc = 0;                // declare and set local variables
    sh_data* p_data;
    char buffer[RECORD_LEN+1];
    char name[RECORD_LEN-3];
    double l_gpa = 0;
    /****************************************
    * attach the shared memory id to the child process 
    * use p_data as a handle to the shared memory attached to the process
    * error p_data for success attaching memory to process
    */
    for(int i = 0; i < records/2+1; i++){
      if((rc = read(fd, buffer, RECORD_LEN)) < 0){
        perror("p read");
        // clean up attached memory

        exit (EXIT_FAILURE);
      }
      sscanf(buffer, "%s %lf",name, &l_gpa);
      sleep(0.3);
      //printf("P: %s read: %s, gpa: %f\n", buffer, name, l_gpa);
      if(p_data->gpa < l_gpa){
        /****************
        * update the struct's slots name and GPA as you found a higher GPA
        *****************/
        printf("P: found higher GPA %s: %.1f\n", p_data->name, p_data->gpa);
      }
    }
   /******************
    * detach the p_data handle from the process
    *******************/
    }
  if((close(fd) < 0) || (close(fd2) < 0 )){
    perror("close");
  }
  printf("A: Highest gpa found: %s: %lf\n", g_data->name, g_data->gpa);
  /******************
    * detach the g_data handle from the process
  *******************/
  /******************
    * mark the sh_id for garbage collection and destruction
    * when all child processes terminate
  *******************/

  return EXIT_SUCCESS;
}