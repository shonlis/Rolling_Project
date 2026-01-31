#ifndef Person__H_
#define Person__H_

#include <iostream>
#include <string>
using namespace std;


class Person
{
public:
	enum Gender { Male, Female, Unknown }; 

protected:
    
    string name;
	const int id;
	const int birthYear;
	Gender gender;

	Person(const string& name, int id, int birthYear, Gender gender);

public:
    
    // setters
    bool setGender(Gender gender); 

    //other methods
    virtual void showthis() const = 0
    {
        cout << "Person: " << name << ", ID: " << id << ", Birth Year: "
            << birthYear << ", Gender: " << (gender == Male ? "Male" : gender == Female ? "Female" : "Unknown") << std::endl;
    };
	// getters
	const string& getName() const { return name; };
	int getId() const { return id; };
	int getBirthYear() const { return birthYear; };
	Gender getGender() const { return gender; };

    virtual void toOs(ostream& os) const {}

    //operators overloading
    friend ostream& operator<<(ostream& os, const Person& p);
};

#endif // !Person__H_
