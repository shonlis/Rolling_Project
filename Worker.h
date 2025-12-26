#pragma once

#include "Person.h"

class Worker : public Person
{
protected:
	static int workerNumber;

public:
	Worker();
	~Worker();
};

