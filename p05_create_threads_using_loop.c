#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<pthread.h>

#define N 5

int mails = 0;
pthread_mutex_t mutex;

void* routine() {
    for(int i = 0; i < 1000000; i++){
        pthread_mutex_lock(&mutex);
        mails++;
        pthread_mutex_unlock(&mutex);
        // read mails
        // increment
        // write mails
    }
}



int main(int argc, char* argv[]) {
    pthread_t th[N];
    pthread_mutex_init(&mutex, NULL);
//     for (int i = 0; i < N; i++) {
//         if (pthread_create((th + i), NULL, &routine, NULL) != 0) {
//             perror("Failed to create thread\n");
//             return 1;
//         }
//         printf("Thread %d has started\n", i);
//         if (pthread_join(th[i], NULL) != 0) {
//             return 2;
//         }
//         printf("Thread %d has finished execution\n", i);
//     }
// 
// 
//      If pthread_create and join both are in same for loop
//      if works as sequence, and not as parallel
//      as single thread is created and finished working before
//      other thread is created
// 
// // Thread 0 has started
// // Thread 0 has finished execution
// // Thread 1 has started
// // Thread 1 has finished execution
// // Thread 2 has started
// // Thread 2 has finished execution
// // Thread 3 has started
// // Thread 3 has finished execution
// // Thread 4 has started
// // Thread 4 has finished execution
// // number of mails: 5000000



    for (int i = 0; i < N; i++) {
        if (pthread_create((th + i), NULL, &routine, NULL) != 0) {
            perror("Failed to create thread\n");
            return 1;
        }
        printf("Thread %d has started\n", i);
    }
    for (int i = 0; i < N; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            return 2;
        }
        printf("Thread %d has finished execution\n", i);
    }

// Thread 0 has started
// Thread 1 has started
// Thread 2 has started
// Thread 3 has started
// Thread 4 has started
// Thread 0 has finished execution
// Thread 1 has finished execution
// Thread 2 has finished execution
// Thread 3 has finished execution
// Thread 4 has finished execution
// number of mails: 5000000

    
    pthread_mutex_destroy(&mutex);
    printf("number of mails: %d\n", mails);

    return 0;
}