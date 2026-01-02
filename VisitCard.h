#ifndef VisitCard__H_
#define VisitCard__H_


#include "department.h"
#include "Worker.h"


class VisitCard
{
public:
	const int VisitCardNumber;
	static int counter;
	// constructors and destructor
	
	VisitCard(const char* purposeOfVisit, const char* visitingDate, department& departmentsToVisit, Worker* hostWorker);
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
	const department& getDepartmentsToVisit() const { return departmentsToVisit; }
	const Worker* getHostWorker() const { return hostWorker; }
	


private:
	char* purposeOfVisit;
	char visitingDate[9];
	const department& departmentsToVisit;
	const Worker* hostWorker;
};

VisitCard::~VisitCard()
{
	delete[]purposeOfVisit;
	delete[]visitingDate;
}


#endif // !VisitCard__H_
