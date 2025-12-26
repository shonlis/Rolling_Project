#ifndef Worker__H_
#define Worker__H_

#include "Person.h"

class Worker : public Person
{
protected:
	static int workerNumber;

public:
	Worker();
	~Worker();
};

#endif // !Worker__H_