#include<iostream>
#include "Person.h"
Person::Person()
{
    id = 0;
    name[0] = '\0';
    password[0] = '\0';
}
Person::Person(int id, const char* name, const char* password)
{
    this->id = id;

    int i = 0;
    while (name[i] != '\0')
    {
        this->name[i] = name[i];
        i++;
    }
    this->name[i] = '\0';

    i = 0;
    while (password[i] != '\0')
    {
        this->password[i] = password[i];
        i++;
    }
    this->password[i] = '\0';
}
const char* Person::getName()const
{
    return name;
}
Person::~Person() {}