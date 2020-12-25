#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <time.h>
#include <unistd.h>

/******************************************************************************
  Demonstrates how to crack an encrypted password using a simple
  "brute force" algorithm. Works on passwords that consist only of 2 uppercase
  letters and a 2 digit integer.

  Compile with:
    cc -o task2_C_3 2039281_Task2_C_3.c -lcrypt

  If you want to analyse the output then use the redirection operator to send
  output to a file that you can view using an editor or the less utility:
    ./task2_C_3 > t2_C_3_output.txt

  Dr Kevan Buckley, University of Wolverhampton, 2018 Modified by Dr. Ali Safaa 2019
******************************************************************************/

int count = 0; // A counter used to track the number of combinations explored so far

/**
 Required by lack of standard function in C.   
*/

void substr(char *dest, char *src, int start, int length)
{
    memcpy(dest, src + start, length);
    *(dest + length) = '\0';
}

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
 This function can crack the kind of password explained above. All combinations
 that are tried are displayed and when the password is found, #, is put at the 
 start of the line. Note that one of the most time consuming operations that 
 it performs is the output of intermediate results, so performance experiments 
 for this kind of program should not include this. i.e. comment out the printfs.
*/

void crack(char *salt_and_encrypted)
{
    int w, x, y, z; // Loop counters
    char salt[7];   // String used in hashing the password. Need space for \0 // incase you have modified the salt value, then should modifiy the number accordingly
    char plain[7];  // The combination of letters currently being checked // Please modifiy the number when you enlarge the encrypted password.
    char *enc;      // Pointer to the encrypted password

    substr(salt, salt_and_encrypted, 0, 6);
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
                        return; //uncomment this line if you want to speed-up the running time, program will find you the cracked password only without exploring all possibilites
                    }
                    // else{
                    //   printf("%-8d%s %s\n", count, plain, enc);
                    // }
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    for (int i = 0; i < 10; i++)
    {
        //Starting Clock
        struct timespec start, finish;
        long long int difference;
        clock_gettime(CLOCK_MONOTONIC, &start);

        //crack("$6$AS$rO24ikvdmsECaZyd.CCYw0tZbkaFSRVtP6.wo5x0YpAj0x9MM0.yUnzNyO5.7S3nL3lhe51pFAJPsiXqDUhOw."); //Copy and Paste your ecrypted password here using EncryptShA512 program
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
