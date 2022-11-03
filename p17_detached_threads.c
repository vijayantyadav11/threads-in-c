#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<unistd.h>
#include<string.h>
#include<sys/syscall.h>

#define THREAD_NUM 2

void* routine(void* arg) {
    sleep(1);
    printf("Finished Execution\n");
}

// int main(int argc, char* argv[]) {
//     pthread_t th[THREAD_NUM];
//     int i;
//     for (int i = 0; i < THREAD_NUM; i++) {
//         if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
//             perror("Failed to create thread\n");
//         }
//         pthread_detach(th[i]);
//     }

//     for (int i = 0; i < THREAD_NUM; i++) {
//         if (pthread_join(th[i], NULL) != 0) {
//             perror("Failed to join thread\n");
//         }
//     }
//     return 0;
// }
// // Output
// Failed to join thread
// : Success
// Failed to join thread
// : Success



// int main(int argc, char* argv[]) {
//     pthread_t th[THREAD_NUM];
//     int i;
//     for (int i = 0; i < THREAD_NUM; i++) {
//         if (pthread_create(&th[i], NULL, &routine, NULL) != 0) {
//             perror("Failed to create thread\n");
//         }
//         pthread_detach(th[i]);
//     }

//     for (int i = 0; i < THREAD_NUM; i++) {
//         if (pthread_join(th[i], NULL) != 0) {
//             perror("Failed to join thread\n");
//         }
//     }
//     pthread_exit(0);
// }
// // Output
// Failed to join thread
// : Success
// Failed to join thread
// : Success
// Finished Execution
// Finished Execution



int main(int argc, char* argv[]) {
    pthread_t th[THREAD_NUM];
    pthread_attr_t detachedThread;
    pthread_attr_init(&detachedThread);
    pthread_attr_setdetachstate(&detachedThread, PTHREAD_CREATE_DETACHED);

    int i;
    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_create(&th[i], &detachedThread, &routine, NULL) != 0) {
            perror("Failed to create thread\n");
        }
    }

    for (int i = 0; i < THREAD_NUM; i++) {
        if (pthread_join(th[i], NULL) != 0) {
            perror("Failed to join thread\n");
        }
    }
    pthread_attr_destroy(&detachedThread);
    pthread_exit(0);
}
// Output
// Failed to join thread
// : Success
// Failed to join thread
// : Success
// Finished Execution
// Finished Execution

// pthread_attr_t used because there might be a case where a thread finish it's execution
// right inbetween pthread_create and pthread_detached because it finished execution
// therefore resources wouldn't be freed automatically as it finshed execution and 
// did not join and was not in detached state.
// in this way we are making sure the thread gets created with detached state set