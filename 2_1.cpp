#include<iostream>
#include<thread>
using namespace std;
class background_task{
    public:
        void operator()() const{
            cout<<"hello       ";
        }
};

int main(){
    background_task f;
    thread my_thread(f);
    my_thread.join();
    return 0;
}







