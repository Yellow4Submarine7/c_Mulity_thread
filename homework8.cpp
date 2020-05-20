#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include<istream>
using namespace std;
int  main ()  
{
 int array[1000];
 omp_lock_t locks[10];
 int histogram[10];
 omp_set_num_threads (5);
 srandom (11);
#pragma omp parallel for
 for (int i = 0; i < 1000; i++){
     array[i] = random () % 10;//生成一个10以内的随机数
     printf("%d ",array[i]);
 };
#pragma omp parallel for
 for (int i = 0; i < 10; i++)  //初始化计数值和锁
{
     omp_init_lock (&locks[i]);
     histogram[i] = 0;
   }
#pragma omp parallel for
 for (int i = 0; i < 1000; i++)
{
    int num = array[i];
    omp_set_lock(&locks[num]);
    histogram[num] = histogram[num]+1;
    omp_unset_lock(&locks[num]);
   }
 for (int i = 0; i < 10; i++)
   printf ("histogram[%d]=%d\n", i, histogram[i]);
 for (int i = 0; i < 10; i++)
   omp_destroy_lock (&locks[i]);
}
