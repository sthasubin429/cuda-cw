/*
To Compile:
    cc -o task2_C_3 2039281_Task2_C_3.c -lcrypt

To Run:
    ./task2_C_3

To Record Output:
    ./task2_C_3 > task2_C_3_output.txt
*/

/*****************************************************
 BY Subin Shrestha
 ID 2039281 

--Modified code to crack code with 3 letters and 2 numbers
--Letters are all uppercase letters.
--Loops over all the possible solutions and compares each encryptions.
******************************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <unistd.h>

int count = 0; // A counter used to track the number of combinations explored so far

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length)
{
    memcpy(dest, src + start, length);
    *(dest + length) = '\0';
}

//To calculate time
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

/**
 The function craks any password with 3 letters and numbers (E.G. HPC20). 
 All combinaction are looped over and compared with the given encryptionn.
*/

void crack(char *salt_and_encrypted)
{
    int w, x, y, z; // Loop counters
    char salt[7];   // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
    char plain[7];  // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
    char *enc;      // Pointer to the encrypted password

    substr(salt, salt_and_encrypted, 0, 6);
    //3 loops for letters and 1 loop for number
    for (w = 'A'; w < 'Z'; w++)
    {
        for (x = 'A'; x <= 'Z'; x++)
        {
            for (y = 'A'; y <= 'Z'; y++)
            {
                for (z = 0; z <= 99; z++)
                {
                    sprintf(plain, "%c%c%c%02d", w, x, y, z);
                    enc = (char *)crypt(plain, salt);
                    count++;
                    if (strcmp(salt_and_encrypted, enc) == 0)
                    {
                        printf("#%-8d%s %s\n", count, plain, enc);
                        return; //Comment line to explore all possible solutions
                    }
                    //Uncommnet lines below to print all possible solutions
                    // else{
                    //   printf("%-8d%s %s\n", count, plain, enc);
                    // }
                }
            }
        }
    }
}

//main function
int main(int argc, char *argv[])
{
    for (int i = 0; i < 10; i++)
    {
        //Starting Clock
        struct timespec start, finish;
        long long int difference;
        clock_gettime(CLOCK_MONOTONIC, &start);

        crack("$6$AS$OIOi9C/gGpmCJBwysT46npeEFQukq.1ro0JX.RTbNW5c8Ra/jvIRtPgpFa/9A02JRI2CZFZENFPES7LkF8O4t1"); //Copy and Paste your ecrypted password here using EncryptShA512 program (BCD20)
        printf("%d solutions explored\n", count);

        //Stopping Clock
        clock_gettime(CLOCK_MONOTONIC, &finish);
        time_difference(&start, &finish, &difference);
        printf("run no %d lasted %lldns or %9.5lfs\n", i, difference, difference / 1000000000.0);
        count = 0;
        printf("##############################################\n");
    }

    return 0;
}
