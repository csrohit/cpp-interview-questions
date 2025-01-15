#include <cstdio>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t mutex;

void * even(void * arg)
{
    long* threadId = reinterpret_cast<long*>(arg);
    printf("Thread%ld: Started\n", *threadId);
    pthread_mutex_lock(&mutex);
    sleep(1);
    pthread_mutex_unlock(&mutex);
    printf("Thread%ld: Finished\n", *threadId);
    return nullptr;
}

int main()
{
    pthread_t t1, t2, t3, t4;
    long data[4] = {1, 2, 3, 4};

    pthread_mutex_init(&mutex, nullptr);

    pthread_create(&t1, nullptr, even, &data[0]);
    pthread_create(&t2, nullptr, even, &data[1]);
    pthread_create(&t3, nullptr, even, &data[2]);
    pthread_create(&t4, nullptr, even, &data[3]);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    pthread_join(t4, nullptr);
    
    pthread_mutex_destroy(&mutex);
    return 0;
}
