/*
To Compile: 
    cc -o task1_6B task1_6B.c -pthread
To Run:
    ./task1_6B
*/
#include <pthread.h>
#include <stdio.h>
int counter;
static void *thread_func(void *_tn)
{
    int i;
    for (i = 0; i < 100000; i++)
        counter++;
    return NULL;
}
int main()
{
    int i, N = 5;
    pthread_t t[N];
    for (i = 0; i < N; i++)
    {
        pthread_create(&t[i], NULL,
                       thread_func, NULL);
        pthread_join(t[i], NULL);
    }
    printf("%d\n", counter);
    return 0;
}