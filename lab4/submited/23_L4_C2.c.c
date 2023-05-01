#include<stdio.h>
#include<math.h>
#include<omp.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>

#define min(x, y) (((x) < (y)) ? (x) : (y))
//  Using the MONOTONIC clock 
#define CLK CLOCK_MONOTONIC
#include <omp.h>
#define THRESHOLD 100 

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


void mergeSort_serial(double arr[], int n, int P){
	int curr_size; 
	for (curr_size=1; curr_size<=n-1; curr_size += curr_size){				
		omp_set_num_threads(P);		
		int left_start;
		#pragma omp parallel for 
		for (left_start=0; left_start<n-1; left_start += 2*curr_size){
			int mid = min(left_start + curr_size - 1, n-1);
			int right_end = min(left_start + 2*curr_size - 1, n-1);
			int l = left_start;
			int r = right_end;
			int m = mid;
			int n1 = m - l + 1;
			int n2 =  r - m;
			int i = 0;
			int j = 0;
			int k = l;
			double *L = (double*)(malloc(n1*sizeof(double)));
			double *R = (double*)(malloc(n2*sizeof(double)));
			for (i = 0; i < n1; i++)	L[i] = arr[l + i];
			for (j = 0; j < n2; j++)	R[j] = arr[m + 1+ j];
			i = 0;
			j = 0;
			k = l;
			while (i < n1 && j < n2){
				if (L[i] <= R[j]){
					arr[k] = L[i];
					i++;
				}
				else{
					arr[k] = R[j];
					j++;
				}
				k++;
			}
			while (i < n1){
				arr[k] = L[i];
				i++;
				k++;
			}
			while (j < n2){
				arr[k] = R[j];
				j++;
				k++;
			}
			free(L);
			free(R);
		}
		//wait for all thread to finish
		#pragma omp barrier
	}
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
	char *problem_name = "matrix_multiplication";
	char *approach_name = "block";
//	char buffer[10];
//	FILE* inputFile;
	FILE* outputFile;
	//	inputFile = fopen(argv[3],"r");

	char outputFileName[50];		
	sprintf(outputFileName,"output/%s_%s_%s_%s_output.txt",problem_name,approach_name,argv[1],argv[2]);

	//***************
	double pi = 0;
	long long i = 0, curr = 0;
	double *a = (double*)(malloc(N*sizeof(double)));
	for (i = 0; i < N; i++){
		a[i] = N-i;
	}
	//***************

	clock_gettime(CLK, &start_alg);	/* Start the algo timer */

	/*----------------------Core algorithm starts here----------------------------------------------*/
	mergeSort_serial(a, N, P);
	/*----------------------Core algorithm finished--------------------------------------------------*/

	clock_gettime(CLK, &end_alg);	/* End the algo timer */
	/* Ensure that only the algorithm is present between these two
	   timers. Further, the whole algorithm should be present. */
	/*for (i = 0; i < N; i++){
		printf("%f ", a[i]);
	}
	printf("\n");*/
	free(a);
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