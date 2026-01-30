#pragma warning(disable: 4996)
#include <iostream>
using namespace std;
#include "Person.h"

Person::Person(const string name, int id, int birthYear, Gender gender) : id(id), birthYear(birthYear), gender(gender), name(name ? name : std::string()) {}

Person::Person(const Person& person) : Person(person.name, person.id, person.birthYear, person.gender) {}

Person::Person(Person&& person) noexcept : id(person.id), birthYear(person.birthYear), gender(person.gender), name(std::move(person.name)) {}

bool Person::setGender(Gender gender)
{
    this->gender = gender;
    return true;
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << "Person Details: " << p.getName() << ": ID = " << p.getId() << ", BirthYear = " << p.getBirthYear() << ", Gender = " << p.getGender() << std::endl;
    p.toOs(os);
    return os;
}
