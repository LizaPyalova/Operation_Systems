#include <Windows.h>
#include <iostream>

using namespace std;
int n;
int index_of_min;
int index_of_max;
int average;
void Min_Max(int* arr) {
	cout << "Thread #1 is started..." << endl << endl;
	int min = (int)arr[0];
	int max = (int)arr[0];
	for (int i = 0; i < n; i++) {
		if (min > (int)arr[i]) {
			min = (int)arr[i];
			index_of_min = i;
		}
		Sleep(7);
		if (max < (int)arr[i]) {
			max = (int)arr[i];
			index_of_max = i;
		}
		Sleep(7);
	}
	cout << "Min element: " << min << endl;
	cout << "Max element: " << max << endl;
	cout << endl << "Thread #1 is finished..." << endl;
}

void Average(int* arr) {
	cout <<endl<< endl<< "Thread #2 is started..." << endl << endl;
	int res = 0;
	for (int i = 0; i < n; i++) {
		res += (int)arr[i];
		Sleep(12);
	}
	res = res / n;
	average = res;
	cout << "Average: " << res << endl;
	cout << endl << "Thread #2 is finished..." << endl;
}

int main() {

	
	cout << "Input dimension of array: ";
	cin >> n;
	cout << endl;
	cout << "Input " << n << " elements of array: ";
	int* array= new int[n];
	for (int i = 0; i < n; i++) cin >> array[i];
	cout << endl;
	HANDLE hThreads[2];
	DWORD ID;
	DWORD ID1;

	hThreads[0] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Min_Max, (void*)array, 0, &ID);
	if (hThreads[0] == NULL) return GetLastError();
	
	hThreads[1] = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Average, (void*)array, 0, &ID1);
	if (hThreads[1] == NULL) return GetLastError();

	WaitForSingleObject(hThreads[0], INFINITE);
	WaitForSingleObject(hThreads[1], INFINITE);
	CloseHandle(hThreads[0]);
	CloseHandle(hThreads[1]);

	int minimum = array[index_of_min];
	int maximum = array[index_of_max];

	for (int i = 0; i < n; i++) {
		if (array[i] == minimum || array[i] == maximum) array[i] = average;
	}

	cout << "New Array: " << endl;
	cout << endl;

	for (int i = 0; i < n; i++) cout << array[i] << " ";
	cout << endl;
	system("pause");
	return 0;
	
}