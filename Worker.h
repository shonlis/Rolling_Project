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
public:
	
	Worker(const Person& person);
	

	void operator=(const Worker& worker) = delete;
	void operator=(const Worker&& worker) = delete;

};


#endif // !Worker__H_