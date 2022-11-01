#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<sys/syscall.h>

#define THREAD_NUM 2

pthread_barrier_t barrier;

void* routine(void* arg) {
    pthread_t th = pthread_self();
    printf("%lu pthread API thread id\n",th);
    printf("%d  is OS level thread id, which is different from pthread API thread id\n", (pid_t) syscall(SYS_gettid));
}

int main(int argc, char* argv[]) {
    pthread_t th[THREAD_NUM];
    int i;
    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread\n");
        }
        // printf("%lu\n",th[i]);
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread\n");
        }
    }
    return 0;
}

