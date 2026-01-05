#ifndef VisitCard__H_
#define VisitCard__H_

#include "department.h"
class Worker;

class VisitCard
{
public:
	const int VisitCardNumber;
	static int counter;
	// constructors and destructor
	
	VisitCard(const char* purposeOfVisit, const char* visitingDate, Department& departmentsToVisit, Worker* hostWorker);
	inline ~VisitCard();

	// disable copy and move c'tors
	VisitCard(const VisitCard& visitCard) = delete;
	VisitCard(const VisitCard&& visitCard) = delete;

//operators overloading
friend ostream& operator<<(ostream& os, const VisitCard& VisitCard);

	//setters
	

	// getters
	const char* getPurposeOfVisit() const { return purposeOfVisit; }
	const char* getVisitingDate() const { return visitingDate; }
	int getVisitCardNumber() const { return VisitCardNumber; }
	const Department& getDepartmentsToVisit() const { return departmentsToVisit; }
	const Worker* getHostWorker() const { return hostWorker; }
	


private:
	char* purposeOfVisit;
    char visitingDate[32];
	const Department& departmentsToVisit;
	const Worker* hostWorker;
};

VisitCard::~VisitCard()
{
	delete[]purposeOfVisit;
}


#endif // !VisitCard__H_
