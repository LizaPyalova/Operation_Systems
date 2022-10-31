#include <iostream>
#include <fstream>
using namespace std;

struct employee
{
    int num;
    char name[10];
    double hours;
};

int main(int argc, char* argv[])
{
    employee emp;
    ifstream fin(argv[0]);
    ofstream fout(argv[2]);
    double salary = atof(argv[3]);
    fout << "Отчет по файлу " << argv[0] << endl;
    fout << "Номер | Имя сотрудника | Часы | Зарплата" << endl;
    while (fin >> emp.num)
    {
        fin >> emp.name >> emp.hours;
        fout << emp.num << " | " << emp.name << " | " << emp.hours << " | " << emp.hours * salary << endl;
    }
}
