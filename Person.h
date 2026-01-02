#ifndef Person__H_
#define Person__H_

class Person
{

protected:

	enum Gender { Male, Female, unknow }; // giving iherritants to use this enum
	char* name;
	const int id;
	const int birthYear;
	Gender gender;

	Person(const Person& person); // copy c'tor for iherritants only
	Person(Person&& person); // move c'tor for iherritants only

public:

	// constructors and destructor
	Person(const char* name, int id, int birthYear, Gender gender);
	~Person() { delete[]name; };


	// getters
	const char* getName() const { return name; };
	int getId() const { return id; };
	int getBirthYear() const { return birthYear; };
	Gender getGender() const { return gender; };

	// setters
	bool setGender(Gender gender); /* you can change your gender */
	
	//operators overloading
	friend ostream& operator<<(ostream& os, const Person& p);

};

#endif // !Person__H_