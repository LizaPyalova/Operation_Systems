#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

wchar_t* convert(const char* elem)
{
    wchar_t* c_elem = new wchar_t[strlen(elem)];
    mbstowcs(c_elem, elem, strlen(elem));
    return c_elem;
}
int main()
{
    setlocale(LC_ALL, ".1251");
    std::string name_of_file;
    int number_emp;
    std::cout << "Write name of file :\n";
    std::cin >> name_of_file;
    std::cout << "Write number of employees :\n";
    std::cin >> number_emp;
    std::string creator = "Creator.exe " + name_of_file + " " + std::to_string(number_emp);
    wchar_t* elem = convert(creator.c_str());
    STARTUPINFO si;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    PROCESS_INFORMATION pi;
    if (!CreateProcess(NULL, elem, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        std::cerr << "ERROR";
        return 0;
    }
    delete[] elem;
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    std::string file;
    double salary;
    std::cout << "Write name of file :\n";
    std::cin >> file;
    std::cout << "Write salary per hour :\n";
    std::cin >> salary;
    std::string reporter = "Reporter.exe " + name_of_file + " " + file + " " + std::to_string(salary);
    elem = convert(reporter.c_str());
    ZeroMemory(&si, sizeof(STARTUPINFO));
    si.cb = sizeof(STARTUPINFO);
    if (!CreateProcess(NULL, elem, NULL, NULL, FALSE, 0, NULL, NULL, &si, &pi))
    {
        std::cerr << "ERROR";
        return 0;
    }
    delete[] elem;
    WaitForSingleObject(pi.hProcess, INFINITE);
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);

    std::ifstream fin(file);
    std::string str;
    while (std::getline(fin, str)) {
        std::cout << str << std::endl;
    }
}