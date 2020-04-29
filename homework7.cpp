#include <bits/types/clock_t.h>
#include <ctime>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#include<iostream>
using namespace std;
int main(int argc,char**argv)
{
    clock_t startTime,endTime;
    startTime = clock();
    int steps=atoi(argv[1]);
    double step = 1.0/steps;
    double sum  = 0,x;
    int i;
    //#pragma omp parallel for
    omp_lock_t lock;
    omp_init_lock(&lock);
    for(i=0;i<=steps;i++){
        omp_set_lock(&lock);
        x = (i+0.5)*step;
    //#pragma omp critical
        sum = sum+4/(1+x*x)*step;
        omp_unset_lock(&lock);
    }
    omp_destroy_lock(&lock);
    printf("pi = %1.20f\n",sum);
    endTime = clock();
    cout << "The run time is: " <<(double)(endTime - startTime) / CLOCKS_PER_SEC << "s" << endl;
    return 0;
}
