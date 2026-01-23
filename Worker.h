#ifndef Worker__H_
#define Worker__H_
#include "Person.h"

/*NOTE:
	* 1. there is no need for d'ctor because there is no Dynamic allocation.
	* 2. using copy for Researcher c'tor because of the inheritance.
	* 3. delete overloading operator= and move operator= for the same reason.
	*/

class Worker : public Person
{
protected:
	const int workerNumber;
	static int counter;
	Worker(const Worker& worker); // copy c'tor for Researcher
	Worker(Worker&& worker); // move c'tor for inheritance.

	Worker(const char* name, int id, int birthYear, Gender gender);
	Worker(const Person& person);
public:
	
	
	
	virtual void showthis() const = 0 {
		Person::showthis();
		cout << "Worker Number: " << workerNumber << endl;
	}

	void operator=(const Worker& worker) = delete;
	void operator=(const Worker&& worker) = delete;

	virtual void toOs(ostream& os) const override 
	{ os << "Worker Number: " << workerNumber << endl; }

};


#endif // !Worker__H_