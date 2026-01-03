#include <iostream>
using namespace std;
#include "Person.h"

Person::Person(const char* name, int id, int birthYear, Gender gender) :id(id), birthYear(birthYear), gender(gender)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

Person::Person(const Person& person) : Person(person.name, person.id, person.birthYear, person.gender){}

Person::Person(Person&& person) : id(person.id), birthYear(person.birthYear),gender(person.gender)
{
	this->name = person.name;
	person.name = nullptr;

}

bool Person::setGender(Gender gender)
{
	this->gender = gender;
	return true;
}

ostream& operator<<(ostream& os, const Person& p)
{
	os << "Person Details: " << p.getName() <<": ID = " << p.getId() <<", BirthYear = " <<p.getBirthYear() <<", Gender = "<<p.getGender() << endl;
	return os;
}
