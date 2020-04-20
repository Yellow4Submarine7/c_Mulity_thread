#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
int main(int argc,char**argv)
{
    int steps=atoi(argv[1]);
    double step = 1.0/steps;
    double sum  = 0,x;
    int i;
    #pragma omp parallel for
    for(i=0;i<=steps;i++){
        x = (i+0.5)*step;
    #pragma omp critical
        sum = sum+4/(1+x*x)*step;
    }
    printf("pi = %1.20f\n",sum);
}
