#include <pthread.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct Task
{
    void (*function)(void* arg);
    void*        arg;
    struct Task* next;
} task_t;

typedef struct ThreadPoool
{
    pthread_t*      workers;
    task_t*         head;
    task_t*         tail;
    pthread_mutex_t lock;
    pthread_cond_t  cv;
    int             stop;
    int             numThreads;
} pool_t;

void* do_work(void* arg)
{
    pool_t* pool = (pool_t*)arg;

    while (1)
    {
        pthread_mutex_lock(&pool->lock);
        while ((!pool->stop) && (pool->head == NULL))
        {
            pthread_cond_wait(&pool->cv, &pool->lock);
        }

        if (pool->stop && pool->head == NULL)
        {
            pthread_mutex_unlock(&pool->lock);
            return NULL;
        }

        task_t* task = pool->head;
        pool->head   = task->next;

        if (pool->head == NULL)
        {
            pool->tail = NULL;
        }

        pthread_mutex_unlock(&pool->lock);

        task->function(task->arg);
        free(task);
    }

    return NULL;
}

void thread_pool_init(pool_t* const pool, uint32_t numThreads)
{
    pool->numThreads = numThreads;
    pool->workers    = (pthread_t*)malloc(sizeof(pthread_t) * numThreads);

    pool->head = NULL;
    pool->tail = NULL;
    pthread_mutex_init(&pool->lock, NULL);
    pthread_cond_init(&pool->cv, NULL);

    pool->stop = 0;

    for (uint32_t idx = 0U; idx < numThreads; ++idx)
    {
        pthread_create(pool->workers + idx, NULL, do_work, pool);
    }

    return;
}

void thread_pool_destroy(pool_t* pool)
{
    pthread_mutex_lock(&pool->lock);
    pool->stop = 1;
    pthread_mutex_unlock(&pool->lock);
    pthread_cond_broadcast(&pool->cv);

    for (uint32_t idx = 0U; idx < pool->numThreads; ++idx)
    {
        pthread_join(*(pool->workers + idx), NULL);
    }

    free(pool->workers);
    pthread_mutex_destroy(&pool->lock);
    pthread_cond_destroy(&pool->cv);
}

void thread_pool_enqueue(pool_t* pool, void (*function)(void*), void* arg)
{
    task_t* task   = (task_t*)malloc(sizeof(task_t));
    task->function = function;
    task->arg      = arg;
    task->next     = NULL;

    pthread_mutex_lock(&pool->lock);
    if (NULL != pool->tail)
    {
        pool->tail->next = task;
    }
    else
    {
        pool->head = task;
    }

    pool->tail = task;

    pthread_mutex_unlock(&pool->lock);
    pthread_cond_signal(&pool->cv);
}

void example_work(void* arg)
{
    int id = *(int*)arg;

    printf("Processing task %d on thread %ld\n", id, pthread_self());

    free(arg);

    sleep(1);    
}

int main()
{
    pool_t pool;

    thread_pool_init(&pool, 4);

    for (int i = 0; i < 10; i++)
    {
        int* id = malloc(sizeof(int));
        *id     = i;
        thread_pool_enqueue(&pool, example_work, id);
    }

    thread_pool_destroy(&pool);
    return 0;
}
