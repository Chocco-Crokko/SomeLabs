#include <string>
#include <iostream>
class employee
{
protected:
	std::string _name, _surname, _patronymic;
	double _salary;
	double _allowance;
	int _standing;
public:
	employee(std::string name, std::string surname, std::string patronymic, double salary, double allowance, int standing)
		: _name(name), _surname(surname), _patronymic(patronymic), _salary(salary), _allowance(allowance), _standing(standing)
	{
	}
	virtual double count_salary()
	{
		return _salary * (1 + _standing * (_allowance / 100));
	}
	virtual void print()
	{
		std::cout << _name << std::endl;
		std::cout << _surname << std::endl;
		std::cout << _patronymic << std::endl;
		std::cout << _salary << std::endl;
		std::cout << _allowance << std::endl;
		std::cout << _standing << std::endl;
	}

};

class head : public employee
{
	std::string _organizationName;
	double _additionalAllowance;
public:
	head(std::string name, std::string surname, std::string patronymic, double salary, double allowance, int standing, std::string organizationName, double additionalAllowance)
		: employee(name, surname, patronymic, salary, allowance, standing), _organizationName(organizationName), _additionalAllowance(additionalAllowance)
	{
	}
	double count_salary()
	{
		return (1 + _additionalAllowance / 100) * employee::count_salary();
	}
	void print()
	{
		std::cout << _organizationName << std::endl;
		std::cout << _additionalAllowance << std::endl;
		employee::print();
	}
};

int main()
{
	//head.print() will call
	employee *p = new head("Petr", "Petrov", "Petrovich", 70000, 11.5, 7, "Petrov IP", 7.6);
	p->print();
	std::cout << "***********" << std::endl;
	employee emp("Ivan", "Ivanov", "Ivanovich", 30000, 5, 3);
	std::cout << emp.count_salary() << std::endl;
	emp.print();
	std::cout << "***********" << std::endl;
	head boss("Petr", "Petrov", "Petrovich", 70000, 11.5, 7, "Petrov IP", 7.6);
	std::cout << boss.count_salary() << std::endl;
	boss.print();
	system("pause");
	return 0;
}
