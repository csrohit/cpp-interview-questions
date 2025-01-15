#include <cstdlib>
#include <unistd.h>
#include <cstdio>
#include <pthread.h>
#include <semaphore.h>
#include <sys/sem.h>

sem_t* semaphore;

void* thread_handler(void* arg)
{
    char* name = static_cast<char*>(arg);

    printf("%s: Waiting\n", name);
    sem_wait(semaphore);
    printf("%s: Started\n", name);
    sleep(2);
    printf("%s: Finished\n", name);
    sem_post(semaphore);

    return nullptr;
}

int main()
{
    pthread_t t1, t2, t3, t4;
    // sem_init(&semaphore, 0, 1);

    if ((semaphore = sem_open("./sema", O_CREAT, 0644, 3)) == SEM_FAILED)
    {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    pthread_create(&t1, nullptr, thread_handler, (void*)("Thread1"));
    pthread_create(&t3, nullptr, thread_handler, (void*)("Thread2"));
    pthread_create(&t3, nullptr, thread_handler, (void*)("Thread3"));
    pthread_create(&t4, nullptr, thread_handler, (void*)("Thread4"));
    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);
    pthread_join(t4, nullptr);

    // sem_destroy(&semaphore);
    sem_close(semaphore);

    return (0);
}
