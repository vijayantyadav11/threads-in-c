#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<time.h>

void* roll_dice() {
    int value = (rand() % 6) + 1;
    int* result = malloc(sizeof(int));
    *result = value;
    printf("Thread result: %p\n", result);
    printf("Value: %d\n", value);
    return (void*)result;
}

int main(int argc, char* argv[]) {
    int* res;
    srand(time(NULL));
    pthread_t th;
    if (pthread_create(&th, NULL, &roll_dice, NULL) != 0) {
        return 1;
    }

    if (pthread_join(th, (void **)&res) != 0) {
        return 2;
    }
    printf("Main res: %p\n", res);
    printf("Result: %d\n", *res);
    free(res);
    return 0;
}


// Thread result: 0x7fd2a8000b60
// Value: 2
// Main res: 0x7fd2a8000b60
// Result: 2


// We need to dynamically allocate memory to store value
// otherwise we will get segmentation fault as
// local variable is deallocated as we come out of roll_dice
// fucntion