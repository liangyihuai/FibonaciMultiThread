#include <iostream>

#include <chrono> 
using namespace std::chrono;

using namespace std;

extern unsigned long long arr[10000] = {0};

void main(){
	auto start = high_resolution_clock::now();

	arr[0] = 0;
	arr[1] = 1;
	
	int n = 10000;
	for (int i = 2; i <= n; i++){
		arr[i] = arr[i-1] + arr[i-2];
	}

	auto stop = high_resolution_clock::now();
	//print the execution time 
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "The execution time is: " << duration.count() << endl;

	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}

	system("pause");
}