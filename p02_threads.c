#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

int x = 2;

void* routine() {
    x++;
    sleep(2);
    printf("Value of x:%d\n", x);
    printf("Process id %d\n", getpid());
}

void* routine2() {
    sleep(2);
    printf("Value of x:%d\n", x);
    printf("Process id %d\n", getpid());
}


int main(int argc, char* argv[]) {
    pthread_t t1, t2;
    if (pthread_create(&t1, NULL, &routine, NULL) != 0) {
        return 1;
    }
    if (pthread_create(&t2, NULL, &routine2, NULL) != 0) {
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



// Value of x:3
// Process id 230635
// Value of x:3
// Process id 230635