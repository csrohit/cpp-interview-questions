#include <cstdint>
#include <cstdio>
#include <pthread.h>
#include <unistd.h>

#define COUNT_MAX 20

bool         isEven = true;
pthread_mutex_t mutex  ;
pthread_cond_t  condVar ;

void* printEven(void * arg)
{
    int count = 0;
    printf("Even: Thread Started\n");
    while (count <= COUNT_MAX) {

        pthread_mutex_lock(&mutex);
        while (!isEven) {
            pthread_cond_wait(&condVar, &mutex);
        }
        printf("Even: %d\n", count);
        count += 2;
        isEven = false;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condVar);
    }

    return (nullptr);
}

void* printOdd(void* arg)
{
    int count = 1;
    printf("Odd: Thread Started\n");
    while (count <= COUNT_MAX) {

        pthread_mutex_lock(&mutex);
        while (isEven) {
            pthread_cond_wait(&condVar, &mutex);
        }
        printf("Odd: %d\n", count);
        count += 2;
        isEven = true;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&condVar);
        sleep(1);
    }

    return (nullptr);
}

int main()
{
    pthread_t oddThread, evenThread; 

    pthread_mutex_init(&mutex, nullptr);
    pthread_cond_init(&condVar, nullptr);

    pthread_create(&oddThread, nullptr, printOdd, nullptr);
    pthread_create(&evenThread, nullptr, printEven, nullptr);
    
    printf("Created 2 threads\n");


    pthread_join(oddThread, 0);
    pthread_join(evenThread, 0);

    pthread_cond_destroy(&condVar);
    pthread_mutex_destroy(&mutex);
    return (0);
}
