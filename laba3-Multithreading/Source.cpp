#include <iostream>
#include <random>
#include "Windows.h"
using namespace std;

CRITICAL_SECTION work_arr;
HANDLE* StartThread = nullptr;
HANDLE* Threads = nullptr;
HANDLE* Exit_Thread = nullptr;
HANDLE* Impossible = nullptr;
int* arr =nullptr;
int size1 = 0;
int count_of_threads = 0;
int thread_to_terminate = 0;
int  terminated_threads = 0;
bool* is_terminated = nullptr;

DWORD WINAPI marker(int number) {
    WaitForSingleObject(StartThread[number], INFINITE);

    int number_of_thread = number;
    int random_number = 0;
    int marked_elements = 0;
    HANDLE ThreadFlags[] {StartThread[number], Exit_Thread[number] };
    DWORD flag_number =0;
    
    srand(number);

    while (true) {
        random_number = rand() % size1;
        if (arr[random_number] == 0) {
            EnterCriticalSection(&work_arr);
            Sleep(5);
            arr[random_number] = number_of_thread + 1;
            marked_elements++;
            Sleep(5);
            LeaveCriticalSection(&work_arr);
        }
        else {
            EnterCriticalSection(&work_arr);

            cout << "Number of thread is " << number_of_thread + 1 << endl;
            cout << "Number of marked elements is " << marked_elements << endl;
            cout << "Index impossible to mark is " << random_number << endl;
            cout << endl;
            LeaveCriticalSection(&work_arr);
            SetEvent(Impossible[number_of_thread]);
            ResetEvent(StartThread[number_of_thread]);
            flag_number = WaitForMultipleObjects(2, ThreadFlags, FALSE, INFINITE);
            if (flag_number == WAIT_OBJECT_0 + 1) {
                EnterCriticalSection(&work_arr);
                for (int i = 0; i < size1; i++)
                    if (arr[i] == number_of_thread + 1)
                        arr[i] = 0;
                LeaveCriticalSection(&work_arr);
                cout << endl;
                ExitThread(0);
            }
            else {
                ResetEvent(Impossible[number_of_thread]);
                continue;
            }
            
        }
    }
}


int main()
{
    InitializeCriticalSection(&work_arr);

    cout << "Input size of array: ";
    cin >> size1;
    arr = new int[size1] {};
    for (int i = 0; i < size1; i++) arr[i] = 0;
    cout << "Input count of threads: ";
    cin >> count_of_threads;

    Threads = new HANDLE[count_of_threads];                                       
    Exit_Thread = new HANDLE[count_of_threads];                                    
    Impossible = new HANDLE[count_of_threads];                             
    StartThread = new HANDLE[count_of_threads];
    is_terminated = new bool[count_of_threads] {};

    for (int i = 0; i < count_of_threads; i++) {
        Threads[i] = CreateThread(NULL, 1, (LPTHREAD_START_ROUTINE)marker, (LPVOID)(i), NULL, NULL);     
        StartThread[i] = CreateEvent(NULL, TRUE, FALSE, NULL);                 
        Exit_Thread[i] = CreateEvent(NULL, TRUE, FALSE, NULL);                 
        Impossible[i] = CreateEvent(NULL, TRUE, FALSE, NULL);             
    }

    while (terminated_threads != count_of_threads) {

        for (int i = 0; i < count_of_threads; i++)
            if (!is_terminated[i]) {
                ResetEvent(Impossible[i]);
                SetEvent(StartThread[i]);
            }

        WaitForMultipleObjects(count_of_threads, Impossible, TRUE, INFINITE);

        EnterCriticalSection(&work_arr);
        cout << "Your array is:  ";
        for (int i = 0; i < size1; i++)
           cout << arr[i] << " ";
        cout << endl;
        LeaveCriticalSection(&work_arr);

        cout << "Thread to terminate: ";
        cin >> thread_to_terminate;
        if (is_terminated[thread_to_terminate - 1])
            cout << "This thread has been terminated...Oops" << endl;
        else {
            is_terminated[thread_to_terminate - 1] = true;
            terminated_threads++;
            SetEvent(Exit_Thread[thread_to_terminate - 1]);
            WaitForSingleObject(Threads[thread_to_terminate - 1], INFINITE);
            CloseHandle(Threads[thread_to_terminate - 1]);
            CloseHandle(Exit_Thread[thread_to_terminate - 1]);
            CloseHandle(StartThread[thread_to_terminate - 1]);
        }

        EnterCriticalSection(&work_arr);
        cout << "Your array is:  ";
        for (int i = 0; i < size1; i++)
            cout << arr[i] << ' ';
        cout << endl;
        LeaveCriticalSection(&work_arr);
    }

    delete arr; 
    arr = nullptr;
    delete is_terminated; 
    is_terminated = nullptr;
    for (int i = 0; i < count_of_threads; i++)
        CloseHandle(Impossible[i]);

    cout << "DONE" << endl;
}