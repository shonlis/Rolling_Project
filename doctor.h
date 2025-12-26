#ifndef doctor__H_
#define doctor__H_

#include "Worker.h"
class doctor : public Worker
{
private:
	char* Specialization;
public:	
	doctor();
	~doctor();

};

#endif // !doctor__H_