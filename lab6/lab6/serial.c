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
	char *problem_name = "matrix_multiplication";
	char *approach_name = "block";
	//	char buffer[10];
	//	FILE* inputFile;
	FILE *outputFile;
	//	inputFile = fopen(argv[3],"r");

	char outputFileName[50];
	sprintf(outputFileName, "output/%s_%s_%s_%s_output.txt", problem_name, approach_name, argv[1], argv[2]);

	/*----------------INPUT/OUPUT operations start here-----------------------------*/
	int i, j, k;
	double **a = (double **)malloc(sizeof(double *) * N);
	for (i = 0; i < N; i++)
	{
		a[i] = (double *)malloc(sizeof(double) * N);
	}

	double **q = (double **)malloc(sizeof(double *) * N);
	for (i = 0; i < N; i++)
	{
		q[i] = (double *)malloc(sizeof(double) * N);
	}
	double **r = (double **)malloc(sizeof(double *) * N);
	for (i = 0; i < N; i++)
	{
		r[i] = (double *)malloc(sizeof(double) * N);
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			a[i][j] = rand() % 10;
		}
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			q[i][j] = 0;
		}
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			r[i][j] = 0;
		}
	}
	// double a[8][8] = {{6.00000, 4.00000, 5.00000, 3.00000, 3.00000, 2.00000, 9.00000, 1.00000},
	// 				  {0.00000, 0.00000, 0.00000, 2.00000, 5.00000, 8.00000, 4.00000, 1.00000},
	// 				  {0.00000, 0.00000, 4.00000, 6.00000, 7.00000, 8.00000, 5.00000, 2.00000},
	// 				  {0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 9.00000, 6.00000},
	// 				  {0.00000, 0.00000, 0.00000, 0.00000, 1.00000, 2.00000, 8.00000, 6.00000},
	// 				  {0.00000, 4.00000, 6.00000, 7.00000, 8.00000, 4.00000, 4.00000, 6.00000},
	// 				  {0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 5.00000},
	// 				  {0.00000, 0.00000, 0.00000, 0.00000, 0.00000, 4.00000, 8.00000, 3.00000}};

	double **at = (double **)malloc(sizeof(double *) * N);
	for (i = 0; i < N; i++)
	{
		at[i] = (double *)malloc(sizeof(double) * N);
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			at[i][j] = a[j][i];
		}
	}

	double **qt = (double **)malloc(sizeof(double *) * N);
	for (i = 0; i < N; i++)
	{
		qt[i] = (double *)malloc(sizeof(double) * N);
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			qt[i][j] = 0;
		}
	}
	/*----------------INPUT/OUPUT operations end here-----------------------------*/

	clock_gettime(CLK, &start_alg); /* Start the algo timer */

	/*----------------------Core algorithm starts here----------------------------------------------*/

	
    
    
 
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            q[i][j] = 0;
            qt[i][j] = 0;
            at[i][j] = a[j][i];
        }
    }

    for (i = 0; i < N; i++)
    {
        double s = 0;
        for (j = 0; j < N-3; j+=4)
        {
            s += at[i][j] * at[i][j];
            s += at[i][j+1] * at[i][j+1];
            s += at[i][j+2] * at[i][j+2];
            s += at[i][j+3] * at[i][j+3];
        }
        for(;j<N;j++)
        {
            s += at[i][j]*at[i][j];
        }
        r[i][i] = sqrt(s);
        for (j = 0; j < N-3; j+=4)
        {
            qt[i][j] = at[i][j] / r[i][i];
            qt[i][j+1] = at[i][j+1] / r[i][i];
            qt[i][j+2] = at[i][j+2] / r[i][i];
            qt[i][j+3] = at[i][j+3] / r[i][i];
        }
        for(;j<N;j++)
        {
            qt[i][j] = at[i][j] / r[i][i];
        }
        for (j = i + 1; j < N; j++)
        {
            double s = 0;
            for (k = 0; k < N; k+=4)
            {
                s += at[j][k] * qt[i][k]
                    + at[j][k+1] * qt[i][k+1]
                    + at[j][k+2] * qt[i][k+2]
                    + at[j][k+3] * qt[i][k+3];
            }
            r[i][j] = s;
            for (k = 0; k < N; k+=4)
            {
                at[j][k] -= r[i][j] * qt[i][k];
                at[j][k+1] -= r[i][j] * qt[i][k+1];
                at[j][k+2] -= r[i][j] * qt[i][k+2];
                at[j][k+3] -= r[i][j] * qt[i][k+3];
            }
        }
    }

    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            a[i][j] = at[j][i];
        }
    }
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			q[i][j] = qt[j][i];
		}
	}

	// Print results
	printf("Q matrix:\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%f ", q[i][j]);
		}
		printf("\n");
	}
	printf("R matrix:\n");
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%f ", r[i][j]);
		}
		printf("\n");
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
	printf("%s,%s,%d,%d,%d,%ld,%d,%ld\n", problem_name, approach_name, N, P, e2e.tv_sec, e2e.tv_nsec, alg.tv_sec, alg.tv_nsec);

	return 0;
}
