#ifndef Department__H_
#define Department__H_

#include "Worker.h";
#include "Visitor.h";

class department 
{
	char* name;
	Worker* workers;
	Visitor* visitors;

public:
	department(const char* name);
	~department();
	const char* getName() const;
	void print() const;
};

#endif // !Department__H_


