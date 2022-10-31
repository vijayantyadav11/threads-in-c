#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>

#define N 9

pthread_barrier_t barrier;

void* routine(void* arg) {
    printf("Waiting at the barrier...\n");
    pthread_barrier_wait(&barrier);
    printf("We passed the barrier...\n");
}

int main(int argc, char* argv[]) {
    pthread_t th[N];
    int i;
    // Waiting at the barrier until 3 thread come at the barrier, after which all 3 start execution at once
    pthread_barrier_init(&barrier, NULL, 3); 
                                        
    for (int i = 0; i < N; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread\n");
        }
    }

    for (int i = 0; i < N; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread\n");
        }
    }
    pthread_barrier_destroy(&barrier);

    return 0;
}

