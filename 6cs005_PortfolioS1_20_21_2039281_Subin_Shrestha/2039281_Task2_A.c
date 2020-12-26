/*
To Compile:
    cc -o task2_A 2039281_Task2_A.c
To Run:
    ./task2_A
To Store Output:
    ./task2_A > task2_A_output.txt
*/
/*****************************************************
 BY Subin Shrestha
 ID 2039281 

 Has original Matrix Multipication Implementation.
 Has improved Matrix Multiplication that uses cache and decreases execution time.
 Both function prints Total time taken to complete.
 The main method runs both the function 10 times.
******************************************************/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//To calculate Time
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
int matMul_Original()
{
    //Varibles to calculate time
    struct timespec original_start, original_finish;
    long long int original_difference;

    //These M,N and P defines row and column of matrices.
    //Update this value to change the size of matrices to be computed.
    //Set same values for all to form a square matrix

    //increasing the value above 900 may cause segmentation Fault.
    int M = 800;
    int N = 750;
    int P = 850;

    int a[N][P], b[P][M], c[N][M];
    int i, j, k;

    //the values of the matrix are given random values between 0 and 70.
    //time taken to assign this value is not added to the final time.
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < P; j++)
        {
            a[i][j] = rand() % 70;
        }
    }

    for (i = 0; i < P; i++)
    {
        for (j = 0; j < M; j++)
        {
            b[i][j] = rand() % 70;
        }
    }

    //Calculates time for computing and prining the value only
    clock_gettime(CLOCK_MONOTONIC, &original_start);

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            c[i][j] = 0;
            for (k = 0; k < P; k++)
            {
                c[i][j] = c[i][j] + a[i][k] * b[k][j];
            }
        }
    }
    //Uncomment lines bleow to print the value of matrix A and B
    // printf("\nThe Value of A\n");
    // for (i = 0; i < N; i++)
    // {
    //     for (j = 0; j < P; j++)
    //     {
    //         printf("%d  ", a[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("\nThe Value of B\n");
    // for (i = 0; i < P; i++)
    // {
    //     for (j = 0; j < M; j++)
    //     {
    //         printf("%d  ", b[i][j]);
    //     }
    //     printf("\n");
    // }

    //Prints the final resultant matrix after multiplication
    //Uncomment lines below to print the results.
    // printf("\nThe results is…\n");
    // for (i = 0; i < N; i++)
    // {
    //     for (j = 0; j < M; j++)
    //     {
    //         printf("%d  ", c[i][j]);
    //     }
    //     printf("\n");
    // }

    //Calulating End Time
    clock_gettime(CLOCK_MONOTONIC, &original_finish);
    time_difference(&original_start, &original_finish, &original_difference);
    printf("Execution time of Original Algorithm %lld ns or %9.5lf s\n", original_difference, original_difference / 1000000000.0);
    return 0;
}
int matMul_Improved()
{
    //Variables to caculate time
    struct timespec improverd_start, improverd_finish;
    long long int improverd_difference;

    //These M,N and P defines row and column of matrices.
    //Update this value to change the size of matrices to be computed.
    //Set same values for all to form a square matrix

    //increasing the value above 900 may cause segmentation Fault.
    int M = 800;
    int N = 750;
    int P = 850;

    int a[N][P], b[P][M], c[N][M];
    int i, j, k;

    //the values of the matrix are given random values between 0 and 70.
    //time taken to assign this value is not added to the final time.
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < P; j++)
        {
            a[i][j] = rand() % 70;
        }
    }

    for (i = 0; i < P; i++)
    {
        for (j = 0; j < M; j++)
        {
            b[i][j] = rand() % 70;
        }
    }

    //Calculates time for computing and prining the value only
    clock_gettime(CLOCK_MONOTONIC, &improverd_start);
    //Defining cache variable
    int cache;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            cache = 0;
            for (k = 0; k < P; k++)
            {
                cache = cache + a[i][k] * b[k][j];
            }
            c[i][j] = cache;
        }
    }
    //Uncomment lines bleow to print the value of matrix A and B
    // printf("\nThe Value of A\n");
    // for (i = 0; i < N; i++)
    // {
    //     for (j = 0; j < P; j++)
    //     {
    //         printf("%d  ", a[i][j]);
    //     }
    //     printf("\n");
    // }

    // printf("\nThe Value of B\n");
    // for (i = 0; i < P; i++)
    // {
    //     for (j = 0; j < M; j++)
    //     {
    //         printf("%d  ", b[i][j]);
    //     }
    //     printf("\n");
    // }

    //Prints the final resultant matrix after multiplication
    //Uncomment Lines below to print result
    // printf("\nThe results is…\n");
    // for (i = 0; i < N; i++)
    // {
    //     for (j = 0; j < M; j++)
    //     {
    //         printf("%d  ", c[i][j]);
    //     }
    //     printf("\n");
    // }

    //Stopping time to calculate time
    clock_gettime(CLOCK_MONOTONIC, &improverd_finish);
    time_difference(&improverd_start, &improverd_finish, &improverd_difference);
    printf("Execution time of Improved Algrithm %lld ns or %9.5lf s\n", improverd_difference, improverd_difference / 1000000000.0);
    return 0;
}
int main(int argc, char const *argv[])
{
    for (int i = 0; i < 10; i++)
    {
        matMul_Original();
        matMul_Improved();
    }
    return 0;
}
