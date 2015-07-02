#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <iterator>
#include <memory>
#include "Employee.h"
#include "FixedWageEmployee.h"
#include "UnFixedWageEmployee.h"

using namespace std;

int Employee::_id = 0;

#pragma region Exception

struct ExceptionWrongFileType : public exception
{
	const char * what() const throw()
	{
		return "Bad file name!";
	}
};

#pragma endregion

#pragma region ReadFromFile

void ReadFromFile(string str, list<Employee> &emps)
{
	try
	{
		ifstream file("Data Files\\" + str);
		if (!file.is_open())
			throw ExceptionWrongFileType();
		shared_ptr<Employee> emp;
		string workerName;
		int rate;
		bool fixedPay;
		while (true)
		{
			file >> workerName;
			file >> rate;
			file >> fixedPay;
			if (!file.eof())
			{
				if (fixedPay)
				{
					emp.reset(new FixedWageEmployee());
					emp->NewEmployee(workerName, rate);
					emps.push_back(*emp);
				}
				else
				{
					emp.reset(new UnFixedWageEmployee());
					emp->NewEmployee(workerName, rate);
					emps.push_back(*emp);
				}
			}
			else
				break;
		}
		file.close();
	}
	catch (ExceptionWrongFileType &e)
	{
		cout << e.what() << endl;
	}
};

#pragma endregion

#pragma region WriteToFile

void WriteToFile(list<Employee> &emps)
{
	ofstream file("Data Files\\sortedWorkerList.txt");
	shared_ptr<Employee> emp;
	string workerName;
	double rate;
	bool fixedPay;
	for (auto pos = emps.begin(); pos != emps.end(); ++pos)
	{
		workerName = pos->GetWorkerName();
		rate = pos->GetRate();
		fixedPay = pos->GetFixedPay();
		file << workerName << "\t" << rate << "\t" << static_cast<int>(fixedPay) << endl;
	}
	file.close();
}

#pragma endregion

#pragma region SortPredicate

bool SortByName(Employee &f, Employee &s)
{
	unsigned int i = 0;
	while ((i < f.GetWorkerName().length()) && (i < s.GetWorkerName().length()))
	{
		if (tolower(f.GetWorkerName()[i] < s.GetWorkerName()[i])) return true;
		else if (tolower(f.GetWorkerName()[i] > s.GetWorkerName()[i])) return false;
		++i;
	}
	return (f.GetWorkerName().length() < s.GetWorkerName().length());
};

bool SortBySalary(Employee &f, Employee &s)
{
	if (f.GetSalary() > s.GetSalary())
		return true;
	else if (f.GetSalary() < s.GetSalary())
		return false;
	else
		SortByName(f, s);
};

#pragma endregion


int main()
{
	list<Employee> emps;
	
	//e) Организовать обработку некорректного формата входного файла.
	string file_name = "notExisting.xtx";
	ReadFromFile(file_name, emps);
	cout << endl << endl;

	//d) Организовать запись и чтение коллекции в / из файл.
	file_name = "worker.txt";
	ReadFromFile(file_name, emps);

	
	cout << "Unsorted list:" << endl;
	for (auto pos = emps.begin(); pos != emps.end(); ++pos)
	{
		pos->Show();
	}
	cout << endl << endl;
	
	/*a) Упорядочить всю последовательность работников по убыванию
		среднемесячного заработка.При совпадении зарплаты – упорядочивать
		данные по алфавиту по имени.Вывести идентификатор работника, имя и
		среднемесячный заработок для всех элементов списка.*/
	emps.sort(SortBySalary);
	cout << "Sorted list:" << endl;
	for (auto pos = emps.begin(); pos != emps.end(); ++pos)
	{
		pos->Show();
	}
	cout << endl << endl;
	
	/*b) Вывести первые 5 имен работников из полученного в пункте а)
		списка.*/
	int i = 5;
	auto pos = emps.begin();
	while (i > 0)
	{		
		cout << "\t" <<  pos->GetWorkerName() << endl;
		--i;
		++pos;
	}
	
	/*c) Вывести последние 3 идентификатора работников из полученного в
		пункте а) списка.*/
	i = 3;
	pos = emps.end();
	while (i > 0)
	{
		--pos;
		--i;
		cout << pos->GetId() << endl;		
	}		
	//d) Организовать запись и чтение коллекции в / из файл.
	WriteToFile(emps);
	return 0;
}