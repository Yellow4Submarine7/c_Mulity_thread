#include <cstdlib>
#include <iostream>
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
//目前只能在N可被M整除时计算正确
using namespace std;

int *sum = new int[20];     //任何一个数组都需要初始化
struct thread_data{
    int thread_id;
    int ave_num;
};

void* sum_job(void* threadarg)    //每个子线程处理一个部分
{
    struct thread_data *my_data;
    my_data = (struct thread_data *) threadarg;
    int n = (int)my_data->thread_id;
    int AVE = (int)my_data->ave_num;
    int start = n*AVE+1;
    int end = start + AVE - 1;
    int i;
    sum[n] = 0;

    for(i=start; i <= end; i++){
        sum[n] = sum[n] + i;
    }
    pthread_exit(0);
}

int main(){
    int N;
    int M;
    cout << "Please input thread number\n";
    cin >> N;
    cout << "Please input count number\n";
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

    printf("sum is %d\n",result);

    free(pthread_id);
    delete []td;
    free(sum);
    return 0;
}


