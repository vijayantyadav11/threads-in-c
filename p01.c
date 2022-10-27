#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int counter = 0;

void* routine(void *arg) {
    printf("Test from '%s'\n",(char *)arg);
    if (counter^1)
        sleep(3);
    printf("End '%s'\n",(char *)arg);
}

int main(int argc, char* argv[]) {
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, "thread 1") != 0) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine, "thread 2") != 0) {
        return 2;
    }
    if (pthread_join(t1, NULL) != 0) {
        return 3;
    }
    if (pthread_join(t2, NULL) != 0) {
        return 4;
    }
    
    return 0;
}