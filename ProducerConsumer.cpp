#include <iostream>           
#include <queue>
#include <thread>             
#include <mutex>          
#include <condition_variable> 
#include <windows.h>
using namespace std;

mutex mtx;
condition_variable produce, consume;  

queue<int> q;     // shared value by producers and consumers, which is the critical section
int maxSize = 20;

void consumer()
{
	while (true)
	{
		//this_thread::sleep_for(chrono::milliseconds(1000));
		Sleep(1);
		unique_lock<mutex> lck(mtx);
		while (q.size() == 0){
			consume.wait(lck);             
		}
		
		q.pop();
		cout << "consumer " << this_thread::get_id() << ": " << q.size() << '\n';

		produce.notify_all();                              
		lck.unlock();
	}
}

void producer(int id)
{
	while (true){
		
		Sleep(1);//  
		unique_lock<mutex> lck(mtx);
		while (q.size() == maxSize){
			produce.wait(lck);
		}
	
		q.push(id);
		cout << "-> producer " << this_thread::get_id() << ": "<< q.size() << '\n';

		consume.notify_all();                                  
		lck.unlock();
	}
}

int main()
{
	thread consumers[2], producers[2];

	
	for (int i = 0; i < 2; ++i)
	{
		consumers[i] = thread(consumer);
		producers[i] = thread(producer, i + 1);  
	}

	
	for (int i = 0; i < 2; ++i)
	{
		producers[i].join();
		consumers[i].join();
	}

	system("pause");
	return 0;
}