#ifndef Person__H_
#define Person__H_

#include <iostream>
#include <string>

class Person
{
public:
    enum Gender { Male, Female, Unknown }; // giving inheritors access to this enum

protected:
    std::string name;
    const int id;
    const int birthYear;
    Gender gender;

    Person(const Person& person); // copy c'tor for inheritors only
    Person(Person&& person) noexcept; // move c'tor for inheritors only

    // constructors and destructor
    Person(const char* name, int id, int birthYear, Gender gender);
    virtual ~Person() = default;

public:
    // getters
    const char* getName() const { return name.c_str(); };
    int getId() const { return id; };
    int getBirthYear() const { return birthYear; };
    Gender getGender() const { return gender; };

    // setters
    bool setGender(Gender gender); /* you can change your gender */

    //other methods
    virtual void showthis() const = 0
    {
        std::cout << "Person: " << name << ", ID: " << id << ", Birth Year: "
            << birthYear << ", Gender: " << (gender == Male ? "Male" : gender == Female ? "Female" : "Unknown") << std::endl;
    };

    virtual void toOs(std::ostream& os) const {}

    //operators overloading
    friend std::ostream& operator<<(std::ostream& os, const Person& p);
};

#endif // !Person__H_
