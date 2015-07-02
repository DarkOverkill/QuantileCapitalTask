#pragma once
#include <iostream>
#include <string>
using namespace std;

class Employee
{
private:
	static int _id;
protected:
	const double _workDays = 20.8;
	const int _workHoursForDay = 8;
	double _salary;
	double _rate;
	bool _fixedPay;
	int _empId;
	string _workerName;
public:
	Employee();
	virtual double GetRate()
	{
		return _rate;
	}
	virtual bool GetFixedPay()
	{
		return _fixedPay;
	}
	virtual int GetId()
	{
		return _empId;
	}
	virtual double GetSalary()
	{
		return _salary;
	}
	virtual string GetWorkerName()
	{
		return _workerName;
	}
	int IncrementId()
	{
		return ++_id;
	}
	virtual void CalculateSalary()
	{
		!_fixedPay ? (_salary = _workDays * static_cast<double>(_workHoursForDay) * _rate) : (_salary = _rate);
	}
	virtual void Show()
	{
		cout << "Id:" <<_empId << "\t" << _workerName << ": " << _salary << "$" << endl;
	}
	virtual void NewEmployee(string name, int rate)
	{
		_workerName = name;
		_rate = rate;
		CalculateSalary();
	}
	~Employee();
};
