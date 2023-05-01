#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void dummy(int);

void dummy(int n) {
    n = 10 * (n/10);
}

int main() {
    int minSize = pow(2, 3);
    int maxSize = pow(2, 25);
    int total = maxSize;

     double *a, *b, *c, *d;
    clock_t start, end;
    int size=minSize;
    for(; size<=maxSize; size*=2) {
        
        /* init data */
        a = (double*) malloc(size * sizeof(double));
        b = (double*) malloc(size * sizeof(double));
        c = (double*) malloc(size * sizeof(double));
        d = (double*) malloc(size * sizeof(double));
        int i=0;
        for(; i<size; i++) {
            b[i]=3;
            c[i]=2;
            d[i]=1;
        }

        int RUNS = total/size;
        double wallTime = 0;

        start = clock();
        int run=0;
        for(; run<RUNS; run++) {
            /* vector triad */
            int ind=0;
            for(; ind<size; ind++) {
                a[ind] = b[ind]+c[ind]*d[ind];
                if(((double)ind)==333.333)
                    dummy(ind);
            }
        }
        end = clock();
        wallTime = (end - start)/((double)CLOCKS_PER_SEC);
        /* Avg throughput */
        double throughput = ((double)sizeof(double) * total * 2)/wallTime;
        printf("%d, %d, %d, %lf\n", size, RUNS, size*RUNS, throughput);

        /* free data */
        free(a);
        free(b);
        free(c);
        free(d);
    }

}

