#ifndef VisitCard__H_
#define VisitCard__H_


#include "department.h"
#include "Worker.h"

class VisitCard
{
private:
	char* purposeOfVisit;
	char* visitingDate;
	department& departmentsToVisit;
	Worker& hostWorker;
};

#endif // !VisitCard__H_
