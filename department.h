#pragma once
class department
{
	char* name;
public:
	department(const char* name);
	~department();
	const char* getName() const;
	void print() const;
};

