#ifndef Person__H_
#define Person__H_

#include <iostream>
using namespace std;

class Person
{
public:
	enum Gender { Male, Female, Unknown }; // giving iherritants to use this enum

protected:

    char* name = nullptr;
	const int id;
	const int birthYear;
	Gender gender;

	Person(const Person& person); // copy c'tor for iherritants only
	Person(Person&& person); // move c'tor for iherritants only

public:

	// constructors and destructor
	Person(const char* name, int id, int birthYear, Gender gender);
	virtual ~Person() { delete[]name; };


	// getters
	const char* getName() const { return name; };
	int getId() const { return id; };
	int getBirthYear() const { return birthYear; };
	Gender getGender() const { return gender; };

	// setters
	bool setGender(Gender gender); /* you can change your gender */
	
	//other methods
	virtual void showthis() const = 0 
	{
		cout << "Person: " << name << ", ID: " << id << ", Birth Year: "
			<< birthYear << ", Gender: " << (gender == Male ? "Male" : gender == Female ? "Female" : "Unknown") << endl;
	};

	virtual void toOs(ostream& os) const {}

	//operators overloading
	friend ostream& operator<<(ostream& os, const Person& p);

};

#endif // !Person__H_