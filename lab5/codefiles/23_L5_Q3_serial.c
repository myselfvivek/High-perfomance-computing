#include<stdio.h>
#include<math.h>
#include<omp.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

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
struct timespec diff(struct timespec start, struct timespec end){
	struct timespec temp;
	if((end.tv_nsec-start.tv_nsec)<0){
		temp.tv_sec = end.tv_sec-start.tv_sec-1;
		temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
	}
	else{
		temp.tv_sec = end.tv_sec-start.tv_sec;
		temp.tv_nsec = end.tv_nsec-start.tv_nsec;
	}
	return temp;
}


int main(int argc, char* argv[])
{
	struct timespec start_e2e, end_e2e, start_alg, end_alg, e2e, alg;
	/* Should start before anything else */
	clock_gettime(CLK, &start_e2e);

	/* Check if enough command-line arguments are taken in. */
	if(argc < 3){
		printf( "Usage: %s n p \n", argv[0] );
		return -1;
	}

	int N=atoi(argv[1]);	/* size of input array */
	int P=atoi(argv[2]);	/* number of processors*/
	char *problem_name = "calculating the value of pi";
	char *approach_name = "integrating function 4/(1+x^2) from 0 to 1 using trapezoidal rule";
//	char buffer[10];
//	FILE* inputFile;
	FILE* outputFile;
	//	inputFile = fopen(argv[3],"r");

	char outputFileName[50];		
	sprintf(outputFileName,"output/%s_%s_%s_%s_output.txt",problem_name,approach_name,argv[1],argv[2]);

	/*----------------INPUT/OUPUT operations start here-----------------------------*/
	int row, col, i, j, k;
	double ** A = (double **)malloc(sizeof(double *) * N);

	for(row=0; row<N; row++){
		A[row] = (double *)malloc(sizeof(double) * N);
	}

	double ** B = (double **)malloc(sizeof(double *) * N);
	for(row=0; row<N; row++){
		B[row] = (double *)malloc(sizeof(double) * N);
	}

	double ** C = (double **)malloc(sizeof(double *) * N);
	for(row=0; row<N; row++){
		C[row] = (double *)malloc(sizeof(double) * N);
	}

	for(row=0; row<N; row++){
		for(col=0; col<N; col++){
			A[row][col] = 1;
			B[row][col] = 2;
			C[row][col] = 0;
		}
	}

	int cacheSize = pow(2,15);//cluster L1d cache = 32K
	//int blockSize = max(N/2,pow(2,5));//sqrt(cacheSize/(3*sizeof(double)));
	int blockSize;
	double temp;
    int s = N;
	int jj,kk;
	if(N/2<pow(2,5))
	    blockSize = N/2;
    
    else
        blockSize = pow(2,5);
	/*----------------INPUT/OUPUT operations end here-----------------------------*/

	clock_gettime(CLK, &start_alg);	/* Start the algo timer */

	/*----------------------Core algorithm starts here----------------------------------------------*/
    
    
    for(jj=0;jj<N;jj+= blockSize){
            for(kk=0;kk<N;kk+= blockSize){
                    for(i=0;i<N;i++){
                            for(j = jj; j<((jj+blockSize)>N?N:(jj+blockSize)); j++){
                                    temp = 0;
                                    for(k = kk; k<((kk+blockSize)>N?N:(kk+blockSize)); k++){
                                            temp += A[i][k]*B[k][j];
                                    }
                                    C[i][j] += temp;
                            }
                    }
            }
    }
	/*----------------------Core algorithm finished--------------------------------------------------*/


	clock_gettime(CLK, &end_alg);	/* End the algo timer */
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


// csv file format - Problem Name | Machine | Problem Size | Algo Time | End to End

