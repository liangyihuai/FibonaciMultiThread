#include <iostream>
#include <thread>

#include <chrono> 
using namespace std::chrono;

using namespace std;

extern unsigned long long arr[10000] = {0};


void fibonacci_even(int n) {

	for (int i = 4; i < n; i = i + 2) {
		arr[i] = 3 * arr[i - 2] - arr[i - 4];
	}
}

void fibonacci_odd(int n) {

	for (int i = 5; i < n; i = i + 2) {
		arr[i] = 3 * arr[i - 2] - arr[i - 4];
	}
}

int main() {
	auto start = high_resolution_clock::now();

	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 1;
	arr[3] = 2;

	int n = 10000;

	std::thread f_even(fibonacci_even, n);
	std::thread f_odd(fibonacci_odd, n);
	f_even.join();
	f_odd.join();
	
	auto stop = high_resolution_clock::now();
	//print the execution time 
	auto duration = duration_cast<microseconds>(stop - start);
	cout << "The execution time is: " << duration.count() << endl;

	for (int i = 0; i < n; i ++) {
		cout << arr[i] << " ";
	}

	system("pause");
	return 0;
}