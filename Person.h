#pragma once
class Person
{
protected:
	int id;
	char name[50];
	char password[20];
public:
	Person();
	Person(int i,const char* name,const char* password);
	virtual void display() = 0;
	virtual void menu() = 0;
	virtual ~Person();
	const char* getName()const;
};