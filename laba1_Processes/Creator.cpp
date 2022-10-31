#include <fstream>
#include <iostream>
#include <vector>
using namespace std;

struct employee
{
	int num;
	char name[10];
	double hours;
};

int main(int argc, char* argv[])
{
	ofstream fout(argv[1]);
	vector<employee> v(atoi(argv[2]));
	for (int i = 0; i < v.size(); ++i)
	{
		cout << "Enter number: ";
		cin >> v[i].num;
		cout << "Enter name: ";
		cin >> v[i].name;
		cout << "Enter hours: ";
		cin >> v[i].hours;
		fout << v[i].num << " " << v[i].name << " " << v[i].hours << endl;
	}
	fout.close();
	return 0;
}