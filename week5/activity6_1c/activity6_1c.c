#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

int print(char* msg){
    for(int i=0; i<1000; i++)
        printf("%s",msg);
    pthread_exit(EXIT_SUCCESS);
}

void main(void){
    pthread_t thread1, thread2;
    char* message1 ="1";
    char* message2 ="0";

    if(pthread_create(&thread1, // line '12' according to the guide
        NULL,
        (void*) &print,
        (void*) message1) != 0){
        perror("thread create failed");
    }
    sleep(0);
    if(pthread_create(&thread2, // line '18' according to the guide
        NULL,
        (void*) &print,
        (void*) message2) != 0){
        perror("thread create failed");
    }

    pthread_join(thread1, NULL); // line '25' according to the guide
    pthread_join(thread2, NULL); // line '26' according to the guide
}
