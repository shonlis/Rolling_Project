#pragma once
class Worker;
class Visitor;
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

