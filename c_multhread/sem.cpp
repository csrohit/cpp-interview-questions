#include <cstdio>
#include <semaphore.h>
#include <unistd.h>
#include <pthread.h>

sem_t semaphore;


void * thread_handler(void * arg)
{
    long* threadId = reinterpret_cast<long*>(arg);
    printf("Thread%ld: Started\n", *threadId);
    sem_wait(&semaphore);
    sleep(1);
    sem_post(&semaphore);
    printf("Thread%ld: Finished\n", *threadId);
    return nullptr;
}

int main()
{
    pthread_t t1, t2, t3, t4;
    long data[4] = {1, 2, 3, 4};

    sem_init(&semaphore, 0, 2);

    pthread_create(&t1, nullptr, thread_handler, &data[0]);
    pthread_create(&t2, nullptr, thread_handler, &data[1]);
    pthread_create(&t3, nullptr, thread_handler, &data[2]);
    pthread_create(&t4, nullptr, thread_handler, &data[3]);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    pthread_join(t4, nullptr);
    
    sem_destroy(&semaphore);
    return 0;
}
