#include <iostream>

using namespace std;

class Base
{
protected:
	string name;
public:
	Base()
	{
		cout << "Base()";
		this->name = "Default Base";
	}
	Base(string name)
	{
		cout << "Base(string name)";
		this->name = name + " Base";
	}
	Base(Base& b)
	{
		cout << "Base(Base& b)";
		this->name = b.name;
	}

	~Base()
	{
		cout << "~Base()\n";
		this->name = "";
	}
};

class Desc : public Base
{
public:
	Desc()
	{
		cout << "Desc()";
		this->name = "Default Desc";
	}
	Desc(string name)
	{
		cout << "Desc(string name)";
		this->name = name + " Desc";
	}
	Desc(Desc& d)
	{
		cout << "Desc(Desc& d)";
		this->name = d.name;
	}

	~Desc()
	{
		cout << "~Desc()";
		this->name = "";
	}
};

void func1(Base  obj)
{
	cout << "func1(Base  obj)";
}
void func2(Base* obj)
{
	cout << "func1(Base*  obj)";
}
void func3(Base& obj)
{
	cout << "func1(Base&  obj)";
}