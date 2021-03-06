/*
To Compile:
    cc -o task1_5 2039281_Task1_5.c
To Run:
    ./task1_5
*/
/*****************************************
 BY Subin Shrestha
 ID 2039281 
 ***************************************/
#include <stdio.h>
int main(int argc, char const *argv[])
{
    int A = 5;
    int B_old = 4;
    int D = 4;

    int C = B_old + D;

    //The Statements below can be executed in parallel wuthout affecting the final output.
    int B_new = A + C;
    int B = C + D;

    //Prints all the values
    printf("Final Values are: \n");
    printf("A = %d \n", A);
    printf("B_old = %d \n", B_old);
    printf("B_new = %d \n", B_new);
    printf("B = %d \n", B);
    printf("C = %d \n", C);
    printf("D = %d \n", D);
    return 0;
}
