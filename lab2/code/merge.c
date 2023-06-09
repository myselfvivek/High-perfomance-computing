#include<stdio.h>
#include<math.h>
#include<omp.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>


// #include <stdio.h>  /* for printf */
// #include <stdint.h> /* for uint64 definition */
// #include <stdlib.h> /* for exit() definition */
// #include<windows.h>
// #define _POSIX_C_SOURCE 200809L
// #define BILLION 1000000000L


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

void merge(double arr[], int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    // Create temp arrays
    double *L=(double*)malloc(sizeof(double)*n1);
    double *R=(double*)malloc(sizeof(double)*n2);
  
    // Copy data to temp arrays 
    // L[] and R[] 
    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];
    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];
  
    // Merge the temp arrays back 
    // into arr[l..r]
    // Initial index of first subarray
    i = 0; 
  
    // Initial index of second subarray
    j = 0; 
  
    // Initial index of merged subarray
    k = l; 
    while (i < n1 && j < n2) 
    {
        if (L[i] <= R[j]) 
        {
            arr[k] = L[i];
            i++;
        }
        else 
        {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
  
    // Copy the remaining elements 
    // of L[], if there are any
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
  
    // Copy the remaining elements of 
    // R[], if there are any 
    while (j < n2) 
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(double arr[],int l, int r)
{
    if (l < r) 
    {
        // Same as (l+r)/2, but avoids 
        // overflow for large l and h
        int m = l + (r - l) / 2;
  
        // Sort first and second halves
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
  
        merge(arr, l, m, r);
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

        int N=atoi(argv[1]);    /* size of input array */
        int P=atoi(argv[2]);    /* number of processors*/
        char *problem_name = "matrix_multiplication";
        char *approach_name = "block";
//      char buffer[10];
//      FILE* inputFile;
        FILE* outputFile;
        //      inputFile = fopen(argv[3],"r");

        char outputFileName[50];
        sprintf(outputFileName,"output/%s_%s_%s_%s_output.txt",problem_name,approach_name,argv[1],argv[2]);

        /*----------------INPUT/OUPUT operations start here-----------------------------*/
        // int i, j, k;
        // int ** adj_mat = (int **)malloc(sizeof(int *) * N);
        // for(i=0; i<N; i++){
        //      adj_mat[i] = (int *)malloc(sizeof(int) * N);
        // }

        // int ** dis = (int **)malloc(sizeof(int *) * N);
        // for(i=0; i<N; i++){
        //      dis[i] = (int *)malloc(sizeof(int) * N);
        // }
        // for(i=0; i<N; i++){
        //      for(j=i+1; j<N; j++){
        //              adj_mat[i][j] = adj_mat[j][i];
        //      }
        // }
        // for(i=0; i<N; i++){
        //      for(j=0; j<N; j++){
        //              if(i == j){
        //                      dis[i][j] = 0;
        //              } else {
        //                      dis[i][j] = adj_mat[i][j];
        //              }
        //      }
        // }

    double *a=(double*)malloc(sizeof(double)*N);
	int i=0;

	for(i=N-1;i>=0;i--)
	{
		a[N-i-1]=i+1;
	}
	// for(i=0;i<N;i++)
	// {
	// 	// b[i]=0;
	// }


        /*----------------INPUT/OUPUT operations end here-----------------------------*/


        clock_gettime(CLK, &start_alg); /* Start the algo timer */

        /*----------------------Core algorithm starts here----------------------------------------------*/

        
    mergeSort(a, 0, N - 1);
// l is for left index and r is 
// right index of the sub-array 
// of arr to be sorted 
// void mergeSort(int arr[], 
//                int l, int r)
// {
//     if (l < r) 
//     {
//         // Same as (l+r)/2, but avoids 
//         // overflow for large l and h
//         int m = l + (r - l) / 2;
  
//         // Sort first and second halves
//         mergeSort(arr, l, m);
//         mergeSort(arr, m + 1, r);
  
//         merge(arr, l, m, r);
//     }
// }

        /*----------------------Core algorithm finished--------------------------------------------------*/

        clock_gettime(CLK, &end_alg);   /* End the algo timer */
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
