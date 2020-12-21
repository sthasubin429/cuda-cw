/**
 * cc -o task2_B StudentID_Task2_B.c -lrt -pthread
 * 
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#define matSize 150

int A[matSize][matSize], B[matSize][matSize], result[matSize][matSize];

int time_difference(struct timespec *start, struct timespec *finish,
                    long long int *difference)
{
    long long int ds = finish->tv_sec - start->tv_sec;
    long long int dn = finish->tv_nsec - start->tv_nsec;

    if (dn < 0)
    {
        ds--;
        dn += 1000000000;
    }
    *difference = ds * 1000000000 + dn;

    return !(*difference > 0);
}

typedef struct parameters
{
    int x, y;
} args;

void *mult(void *arg)
{

    args *p = arg;

    //Calculating Each Element in Result Matrix Using Passed Arguments
    int cache = 0;
    for (int a = 0; a < matSize; a++)
    {
        cache += A[p->x][a] * B[a][p->y];
    }
    result[p->x][p->y] = cache;
    //End Of Thread
    pthread_exit(0);
    
}

int matMuil_multiThreading(int maxThread)
{
    struct timespec start, finish;
    long long int difference;
    clock_gettime(CLOCK_MONOTONIC, &start);
    ///////////////////////

    //Multiply Matrices Using Threads - - - - - - - - - - - - - - - - - - - -//

    //Defining Threads
    pthread_t thread[maxThread];

    //Counter For Thread Index
    int thread_number = 0;

    //Defining p For Passing Parameters To Function As Struct
    args p[matSize * matSize];

    for (int x = 0; x < matSize; x++)
    {

        for (int y = 0; y < matSize; y++)
        {

            //Initializing Parameters For Passing To Function
            p[thread_number].x = x;
            p[thread_number].y = y;

            //Status For Checking Errors
            int status;

            //Create Specific Thread For Each Element In Result Matrix
            status = pthread_create(&thread[thread_number], NULL, mult, (void *)&p[thread_number]);

            //Check For Error
            if (status != 0)
            {
                printf("Error In Threads");
                exit(0);
            }

            thread_number++;
        }
    }

    //Wait For All Threads Done - - - - - - - - - - - - - - - - - - - - - - //

    for (int z = 0; z < (matSize * matSize); z++)
        pthread_join(thread[z], NULL);

    //Print Multiplied Matrix (Result) - - - - - - - - - - - - - - - - - - -//

    // printf(" --- Multiplied Matrix ---\n\n");
    // for (int x = 0; x < matSize; x++)
    // {
    //     for (int y = 0; y < matSize; y++)
    //     {
    //         printf("%5d", result[x][y]);
    //     }
    //     printf("\n\n");
    // }

    //printf(" ---> Time Elapsed : %.6f Sec\n\n", (double)(time(NULL) - start));

    clock_gettime(CLOCK_MONOTONIC, &finish);
    time_difference(&start, &finish, &difference);
    printf("run lasted %lldns or %9.5lfs\n", difference, difference / 1000000000.0);

    //Total Threads Used In Process - - - - - - - - - - - - - - - - - - - -//

    // printf(" ---> Used Threads : %d \n\n", thread_number);
    // for (int z = 0; z < thread_number; z++)
    //     printf(" - Thread %d ID : %d\n", z + 1, (int)thread[z]);

    return 0;
}

int main(int argc, char const *argv[])
{
    int maxThread = matSize * matSize + 100;
    //the values of the matrix are given random values between 0 and 70.
    //time taken to assign this value is not added to the final time.
    for (int a = 0; a < matSize; a++)
    {
        for (int b = 0; b < matSize; b++)
        {
            A[a][b] = rand() % 10;
            B[a][b] = rand() % 10;
        }
    }
    matMuil_multiThreading(maxThread);

    /* code */
    return 0;
}
