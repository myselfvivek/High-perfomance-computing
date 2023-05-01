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

    int n = atoi(argv[1]); /* size of input array */
    int P = atoi(argv[2]); /* number of processors*/
    char *problem_name = "matrix multiplication";
    char *approach_name = "using normal multiplication JIK";
    //  char buffer[10];
    //  FILE* inputFile;
    FILE *outputFile;
    //  inputFile = fopen(argv[3],"r");

    char outputFileName[50];
    sprintf(outputFileName, "output/%s_%s_%s_%s_output.txt", problem_name, approach_name, argv[1], argv[2]);

    /*----------------INPUT/OUPUT operations start here-----------------------------*/
    double **a;
    a = (double **)malloc(n * sizeof(double));
    double **b;
    b = (double **)malloc(n * sizeof(double));
    double **c;
    c = (double **)malloc(n * sizeof(double));
    int i, j, k;
    for (i = 0; i < n; i++)
    {
        a[i] = (double *)malloc(n * sizeof(double));
        b[i] = (double *)malloc(n * sizeof(double));
        c[i] = (double *)malloc(n * sizeof(double));
    }
    for (i = 0; i < n; i++)
    {
        for (j = 0; j < n; j++)
        {
            a[i][j] = 1;
            b[i][j] = 2;
        }
    }

    /*----------------INPUT/OUPUT operations end here-----------------------------*/

    clock_gettime(CLK, &start_alg); /* Start the algo timer */

    /*----------------------Core algorithm starts here----------------------------------------------*/

    for (j = 0; j < n; j++)
    {
        for (i = 0; i < n; i++)
        {
            for (k = 0; k < n; k++)
            {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }

    /*----------------------Core algorithm finished--------------------------------------------------*/

    clock_gettime(CLK, &end_alg); /* End the algo timer */
    /* Ensure that only the algorithm is present between these two
       timers. Further, the whole algorithm should be present. */

    /* Should end before anything else (printing comes later) */
    clock_gettime(CLK, &end_e2e);
    e2e = diff(start_e2e, end_e2e);
    alg = diff(start_alg, end_alg);

    /* problem_name,approach_name,n,p,e2e_sec,e2e_nsec,alg_sec,alg_nsec
       Change problem_name to whatever problem you've been assigned
       Change approach_name to whatever approach has been assigned
       p should be 0 for serial codes!!
     */
    printf("%s,%s,%d,%d,%d,%ld,%d,%ld\n", problem_name, approach_name, n, P, e2e.tv_sec, e2e.tv_nsec, alg.tv_sec, alg.tv_nsec);

    return 0;
}
