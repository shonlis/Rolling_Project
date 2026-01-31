#pragma warning(disable: 4996)
#include "Person.h"

Person::Person(const string& name, int id, int birthYear, Gender gender) :id(id), birthYear(birthYear), gender(gender)
{
	this->name = name;
}

bool Person::setGender(Gender gender)
{
    this->gender = gender;
    return true;
}

ostream& operator<<(ostream& os, const Person& p)
{
    os << "Person Details: " << p.getName() << ": ID = " << p.getId() << ", BirthYear = " << p.getBirthYear() << ", Gender = " << p.getGender() << std::endl;
    p.toOs(os);
    return os;
}
