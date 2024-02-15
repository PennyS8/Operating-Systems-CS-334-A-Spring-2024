//compile and link with "-lpthread"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <values.h>

//declare a struct to be passed to the print function
// struct will contain:
// FILE* an opened FILE* to output file
// char* the message to be printed into a file
// int of the CLI index of the message 
pthread_mutex_t pthr_lock;

// Alter the following print function so it will:
// use struct passed in as an argument
// print to a file
// print struct's <int>: <message> into a file
int print_message_function( void *ptr_arg ){
	char * msg = (char *) ptr_arg;
	printf("Entering Thread\n");
	pthread_mutex_lock(&pthr_lock);
	printf("Inside Thread -- protected area\n");
	//printing struct to file 
	printf("Exiting Thread -- closing protected area\n");
	pthread_mutex_unlock(&pthr_lock);
	pthread_exit(0);
}

// illustrate passing multiple arguments to a threaded method/function 
// CLI arguments ./Lab5Part2 <output file name> <arg> <arg> <arg> ...
// each CLI argument will be processed by a single thread
// each argument will be printed to <output file name> file 
int main(int argc, char* argc[]){
	//dynamically allocate an array of pthread_t one thread per <arg>

	//open <output file name> file for writing

	// allocate struct 

	//setup mutex
	if (pthread_mutex_init(&pthr_lock, NULL) != 0) { 
        perror("mutex init fail"); 
        return 1; 
    } 
    //for loop
        //load arg struct
    	// use argc[] parameters to sent to print message
        //create thread
 
	//threads joined

    //destroy mutex
	pthread_mutex_destroy(&pthr_lock); 
	return EXIT_SUCCESS;
}