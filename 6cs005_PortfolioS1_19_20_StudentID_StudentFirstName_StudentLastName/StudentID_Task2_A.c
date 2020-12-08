#include <stdio.h>
#include <time.h>
#include <stdlib.h>

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
    struct timespec start, finish;
    long long int difference;

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
    clock_gettime(CLOCK_MONOTONIC, &start);

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            c[i][j] = 0;
            int cache = 0;
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
    // printf("\nThe results is…\n");
    // for (i = 0; i < N; i++)
    // {
    //     for (j = 0; j < M; j++)
    //     {
    //         printf("%d  ", c[i][j]);
    //     }
    //     printf("\n");
    // }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    time_difference(&start, &finish, &difference);
    printf("Execution time of Original Algorithm %lldns or %9.5lfs\n", difference, difference / 1000000000.0);
    return 0;
}
int matMul_Improved()
{
    struct timespec start, finish;
    long long int difference;

    //These M,N and P defines row and column of matrices.
    //Update this value to change the size of matrices to be computed.
    //Set same values for all to form a square matrix

    //increasing the value above 900 may cause segmentation Fault.
    // int M = 800;
    // int N = 750;
    // int P = 850;

    int M = 4;
    int N = 3;
    int P = 3;

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

    for (int p = 0; p < N; p++)
    {
        for (int q = 0; q < M; q++)
        {
            c[p][q] = 0;
        }
    }

    //Calculates time for computing and prining the value only
    clock_gettime(CLOCK_MONOTONIC, &start);
    int cache;
    for (i = 0; i < N; i++)
    {
        for (j = 0; j < M; j++)
        {
            cache = 0;
            for (k = 0; k < P; k++)
            {
                //c[i][j] = c[i][j] + a[i][k] * b[k][j];
                cache = cache + a[i][k] * b[k][j];
            }
            c[i][j] = cache;
            printf("\nThe results is…\n");
            for (int p = 0; p < N; p++)
            {
                for (int q = 0; q < M; q++)
                {
                    printf("%d  ", c[p][q]);
                }
                printf("\n");
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
    // printf("\nThe results is…\n");
    // for (i = 0; i < N; i++)
    // {
    //     for (j = 0; j < M; j++)
    //     {
    //         printf("%d  ", c[i][j]);
    //     }
    //     printf("\n");
    // }

    clock_gettime(CLOCK_MONOTONIC, &finish);
    time_difference(&start, &finish, &difference);
    printf("Execution time of Improved Algrithm %lldns or %9.5lfs\n", difference, difference / 1000000000.0);
    return 0;
}
int main(int argc, char const *argv[])
{
    //matMul_Original();
    matMul_Improved();

    return 0;
}
