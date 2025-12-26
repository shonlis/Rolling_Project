#ifndef Person__H_
#define Person__H_

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

#endif // !Person__H_