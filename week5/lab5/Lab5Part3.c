#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/* #include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/sem.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <errno.h>
*/

#define Left(p)	(p)
#define Right(p) (((p)+1) % N)

typedef	int * semaphore;

semaphore chopstick[100];
int fork(void);
semaphore makeSemaphore(void);
void philosopher(int me);
void pickUp (int me);
int pipe (int pd[2]);
void putDown(int me);
int read(int fd, void *buf, unsigned len);
void signal (semaphore s);
void wait(semaphore s);
void sleep(unsigned seconds);
int write(int fd, void *buf, unsigned len);

int N;
int BusyEating;
int BusyThinking;

int main(int argc, char *argv[]){
	int i;
	if (argc == 3){
		N = atoi(argv[1]);
		BusyEating = BusyThinking = atoi(argv[2]);
	}else{
		printf("Usage: ./Lab5Part3 <N philosophers> <x time spend eating>\n");
		exit(1);
	}
	
	for (i=0; i < N; ++i){
		chopstick[i] = makeSemaphore();
		signal(chopstick[i]);
	}
	for (i=0; i < N - 1; ++i){
		if (fork() == 0)
			break;
	}
	philosopher (i);
	return 0;
}

void pickUp (int me){
	if (me ==0){
		wait(chopstick[Right(me)]);
		printf("Ph: %d picks up right chopstick \n", me);
		sleep (1);		/*simulate picking up chopstick-enourage deadlock */
		wait(chopstick[Left(me)]);
		printf("Ph: %d picks up left chopstick \n", me);
	}else{
		wait(chopstick[Left(me)]);
		printf("Ph: %d pick up left chopstick \n", me);
		sleep(1);
		wait(chopstick[Right(me)]);
		printf("Ph: %d pick up right chopstick \n", me);
	}
}

void putDown(int me){
	signal(chopstick[Left(me)]);
	signal(chopstick[Right(me)]);
	printf("Ph: %d done eating and gave up right and left chopstick \n", me);
}


void philosopher (int me){
	char *s;
	int i= 1 ;

	for (;;++i){
		pickUp(me);
		s = ( i==1 ? "st" : i==2 ? "nd" : i==3 ? "rd" : "th");
		printf("Ph: %d eating for the %d%s time \n",me,i,s);
		sleep(BusyEating);
		putDown(me);
		printf("Ph: %d thinking \n", me);
		sleep (BusyThinking);
	}
}

semaphore makeSemaphore(void){
	int *sema;
	sema = calloc (2, sizeof(int));
	pipe(sema);
	return sema;
}

void wait(semaphore s){
	int readBuf;

	if(read(s[0], &readBuf,1) <= 0)	{
		printf("Error: wait() failed, check semaphore creation.\n");
		exit(1);
	}
}

void signal (semaphore s){
	if(write(s[1],"x", 1) <= 0){
		printf("Error: write() failed check semaphore creation.\n");
		exit(1);
	}
}
