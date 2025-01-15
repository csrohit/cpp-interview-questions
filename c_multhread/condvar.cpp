#include <cstdio>
#include <pthread.h>
#include <unistd.h>

pthread_mutex_t mutex;
pthread_cond_t  cv;
bool isOdd = true;

void *even(void *arg)
{
    int count = 2;

    while (count < 21)
    {
        pthread_mutex_lock(&mutex);
        while (isOdd)
            pthread_cond_wait(&cv, &mutex);
        printf("%d\n", count);
        sleep(1);
        isOdd = true;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cv);
        count +=2;
    }
    return nullptr;
}

void *odd(void *arg)
{
    int count = 1;

    while (count < 21)
    {
        pthread_mutex_lock(&mutex);
        while (!isOdd)
            pthread_cond_wait(&cv, &mutex);
        printf("%d\n", count);
        sleep(1);
        isOdd = false;
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cv);
        count +=2;
    }
    return nullptr;
}

int main()
{
    pthread_t t1, t2;

    pthread_mutex_init(&mutex, nullptr);

    pthread_create(&t1, nullptr, even, nullptr);
    pthread_create(&t2, nullptr, odd, nullptr);

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);

    pthread_mutex_destroy(&mutex);
    return 0;
}

