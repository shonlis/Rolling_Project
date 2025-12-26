#pragma once
class hospital
{
	char* name;
public:	
	hospital(const char* name);
	~hospital();
	const char* getName() const;
	void print() const;
};

