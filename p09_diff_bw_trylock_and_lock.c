#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

pthread_mutex_t mutex;

// /* Lock code*/
// void* routine() {
//         pthread_mutex_lock(&mutex);
//         printf("got lock\n");
//         sleep(1);
//         pthread_mutex_unlock(&mutex);
// }


/* Trylock code*/
void* routine() {
    if (pthread_mutex_trylock(&mutex) == 0) {
        printf("got lock\n");
        sleep(1);
        pthread_mutex_unlock(&mutex);
    } else {
        printf("Didn't get lock\n");
    }
}


int main(int argc, char* argv[]) {
    pthread_t th[4];
    pthread_mutex_init(&mutex, NULL);
    for (int i = 0; i < 4; i++) {
        if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
            perror("Failed to create thread\n");
        }
    }

    for (int i = 0; i < 4; i++) {
        if (pthread_join(th[i],NULL) != 0) {
            perror("Failed to join thread\n");
        }
    }
    pthread_mutex_destroy(&mutex);

    return 0;
}

