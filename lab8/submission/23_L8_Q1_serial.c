#include <stdio.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
//  Using the MONOTONIC clock
#define CLK CLOCK_MONOTONIC

/* Function to compute the difference between two points in time */
struct timespec diff(struct timespec start, struct timespec end);

/*
   Function to computes the difference between two time instances

   Taken from - http://www.guyrutenberg.com/2007/09/22/profiling-code-using-clock_gettime/

   Further reading:
http://stackoverflow.com/questions/6749621/how-to-create-a-high-resolution-timer-in-linux-to-measure-program-performance
http://stackoverflow.com/questions/3523442/difference-between-clock-realtime-and-clock-monotonic
 */
struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if ((end.tv_nsec - start.tv_nsec) < 0)
    {
        temp.tv_sec = end.tv_sec - start.tv_sec - 1;
        temp.tv_nsec = 1000000000 + end.tv_nsec - start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec - start.tv_sec;
        temp.tv_nsec = end.tv_nsec - start.tv_nsec;
    }
    return temp;
}

int main(int argc, char *argv[])
{
    struct timespec start_e2e, end_e2e, start_alg, end_alg, e2e, alg;
    /* Should start before anything else */
    clock_gettime(CLK, &start_e2e);

    /* Check if enough command-line arguments are taken in. */
    if (argc < 3)
    {
        printf("Usage: %s n p \n", argv[0]);
        return -1;
    }

    int N = atoi(argv[1]); /* size of input array */
    int P = atoi(argv[2]); /* number of processors*/
    char *problem_name = "PI using random numbers";
    char *approach_name = "iterative";
    //	char buffer[10];
    //	FILE* inputFile;
    FILE *outputFile;
    //	inputFile = fopen(argv[3],"r");

    char outputFileName[50];
    sprintf(outputFileName, "output/%s_%s_%s_%s_output.txt", problem_name, approach_name, argv[1], argv[2]);

    /*----------------INPUT/OUPUT operations start here-----------------------------*/
    float **a = (float **)malloc(N * sizeof(float *));
    int i, j, k;
    for (i = 0; i < N; i++)
        a[i] = (float *)malloc(N * sizeof(float));

    float *b = (float **)malloc(N * sizeof(float));

    for (i = 0; i < N; i++)
    {
        for (j = 0; j < N; j++)
        {
            if (i == j)
                a[i][j] = 2;
            else if (abs(i - j) == 1)
                a[i][j] = -1;
            else
                a[i][j] = 0;
        }
        b[i] = rand() % 10000;
    }

    /*-------------INPUT/OUPUT operations end here-----------------------------*/

    clock_gettime(CLK, &start_alg); /* Start the algo timer */
    // for (i = 0; i < N; i++)
    // {
    //     for (j = i + 1; j < N; j++)
    //     {
    //         float temp = a[i][j];
    //         a[i][j] = a[j][i];
    //         a[j][i] = temp;
    //     }
    // }

    /*----------------------Core algorithm starts here----------------------------------------------*/
    // row oriented
    for (i = 0; i < N - 1; i++)
    {
        for (j = i + 1; j < N; j += 2)
        {
            if (a[i][i] == 0)
                continue;
            float temp1 = a[j][i] / a[i][i], temp2;
            if (j + 1 < N)
                temp2 = a[j + 1][i] / a[i][i];
            for (k = i; k < N; k++)
            {
                a[j][k] = a[j][k] - temp1 * a[i][k];
                if (j + 1 < N)
                    a[j + 1][k] = a[j + 1][k] - temp2 * a[i][k];
            }
            b[j] = b[j] - temp1 * b[i];
            if (j + 1 < N)
                b[j + 1] = b[j + 1] - temp2 * b[i];
        }
    }

    for (i = N - 1; i >= 0; i--)
    {
        if (a[i][i] == 0)
            continue;
        for (j = i + 1; j < N; j++)
        {
            b[i] = b[i] - a[i][j] * b[j];
        }
        b[i] = b[i] / a[i][i];
    }

    // column oriented

    // for (i = 0; i < N - 1; i++)
    // {
    //     for (j = i + 1; j < N; j++)
    //     {
    //         float temp1 = a[i][j] / a[i][i];
    //         for (k = i; k < N; k++)
    //         {
    //             a[k][j] -= temp1 * a[k][i];
    //         }
    //         b[j] = b[j] - temp1 * b[i];
    //     }
    // }

    // for (i = N - 1; i >= 0; i--)
    // {
    //     float temp = b[i];
    //     for (j = i + 1; j < N; j++)
    //     {
    //         temp = temp - a[j][i] * b[j];
    //     }
    //     b[i] = temp / a[i][i];
    // }
    /*----------------------Core algorithm finished--------------------------------------------------*/

    clock_gettime(CLK, &end_alg); /* End the algo timer */
    /* Ensure that only the algorithm is present between these two
       timers. Further, the whole algorithm should be present. */

    // free all the matrix
    /* Should end before anything else (printing comes later) */
    clock_gettime(CLK, &end_e2e);
    e2e = diff(start_e2e, end_e2e);
    alg = diff(start_alg, end_alg);

    /* problem_name,approach_name,N,p,e2e_sec,e2e_nsec,alg_sec,alg_nsec
       Change problem_name to whatever problem you've been assigned
       Change approach_name to whatever approach has been assigned
       p should be 0 for serial codes!!
     */
    printf("%s,%s,%d,%d,%d,%ld,%d,%ld\n", problem_name, approach_name, N, P, e2e.tv_sec, e2e.tv_nsec, alg.tv_sec, alg.tv_nsec);

    return 0;
}
