#include <cstdlib>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<mutex>
//目前只能在N可被M整除时计算正确x
//目前所有情况都能整除正确
using namespace std;

int *sum = new int[20];     //任何一个数组都需要初始化
struct thread_data{
    int thread_id;
    int ave_num;
};

void* sum_job(void* threadarg)    //每个子线程处理一个部分
{
    mutex my_mutex;
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    int n = (int)my_data->thread_id;
    int AVE = (int)my_data->ave_num;
    int start = n*AVE+1;
    int end = start + AVE - 1;
    int i;
    sum[n] = 0;

    for(i=start; i <= end; i++){
        my_mutex.lock();
        sum[n] = sum[n] + i;
        my_mutex.unlock();
    }
     printf("线程id是 %d,start = %d,end = %d,计算结果为 %d \n",n,start,end,sum[n]);

    pthread_exit(0);
}

int main(){
    int N;
    int M;
    cout << "Please input thread number:\n";
    cin >> N;
    cout << "Please input count number:\n";
    cin >> M;
    pthread_t *pthread_id = NULL;
    thread_data *td = new thread_data[N];
    int i;
    int aveN;
    aveN = M/N;
    int result = 0;

    pthread_id = (pthread_t*)malloc(N * sizeof(pthread_t));
    for(i=0;i<N;i++){
        td[i].thread_id = i;
        td[i].ave_num = aveN;
        pthread_create(pthread_id+i,NULL,sum_job,(void *)&td[i]);
    }

    for(i=0;i<N;i++){
        pthread_join(pthread_id[i],NULL);
        result += sum[i];
    }
//以下部分在主线程计算剩余未分配的数组
    int main_start;
    int main_end;
    int main_sum;
    main_sum = 0;
    main_start = N*aveN+1;
    main_end = M;
    for (i=main_start;i<main_end+1;i++){
        main_sum = main_sum+i;
    }
    printf("main_start = %d,main_end = %d,main_sum = %d\n",main_start,main_end,main_sum);
    result = result+main_sum;
    printf("sum is %d\n",result);

    free(pthread_id);
    delete []td;
    free(sum);
    return 0;
}


