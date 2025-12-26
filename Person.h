#pragma once


class Person
{
private:
	enum Gender {Male,Female,unknow};
	
protected:
	char* name;
	int id;
	int birthYear;
	Gender gender;

public:
	Person();
	~Person();
};

