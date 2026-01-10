#ifndef VisitCard__H_
#define VisitCard__H_
#pragma warning(disable: 4996)

#include "Department.h"
class Worker;

class VisitCard
{
public:
	const int VisitCardNumber;
	static int counter;
	// constructors and destructor

	VisitCard(const char* purposeOfVisit, const char* visitingDate, Department& departmentsToVisit, char* hostWorker);

	inline ~VisitCard();

	// disable copy and move c'tors
	VisitCard(const VisitCard& visitCard) = delete;
	VisitCard(const VisitCard&& visitCard) = delete;

	//operators overloading
	friend ostream& operator<<(ostream& os, const VisitCard& VisitCard);

	//setters
	void setHostWorker(const char* hostWorker)
	{
		delete[] this->hostWorker;
		if (hostWorker)
		{
			size_t len = strlen(hostWorker) + 1;
			this->hostWorker = new char[len];
			strncpy(this->hostWorker, hostWorker, len);
		}
		else
		{
			this->hostWorker = nullptr;
		}
	}

	// getters
	const char* getPurposeOfVisit() const { return purposeOfVisit; }
	const char* getVisitingDate() const { return visitingDate; }
	int getVisitCardNumber() const { return VisitCardNumber; }
	const Department& getDepartmentsToVisit() const { return departmentsToVisit; }
	const char* getHostWorker() const { return hostWorker; }

private:
	char* purposeOfVisit;
	char visitingDate[32];
	const Department& departmentsToVisit;
	char* hostWorker;
};

VisitCard::~VisitCard()
{
	if(purposeOfVisit)
	{
		delete[] purposeOfVisit;
	}
	if(hostWorker)
	{
		delete[] hostWorker;
	}
}


#endif // !VisitCard__H_