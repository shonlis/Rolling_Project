#ifndef VisitCard__H_
#define VisitCard__H_
#include "Department.h"

class VisitCard
{
private:
    const int VisitCardNumber;
    static int counter;

    string purposeOfVisit;
    string visitingDate;
    const Department& departmentsToVisit;
    string hostWorker;

public:
	VisitCard(const string& purposeOfVisit, const string& visitingDate, const Department& departmentsToVisit, const string& hostWorker = "there isn't");

    // disable assignment
    VisitCard& operator=(const VisitCard&) = delete;

	//operators overloading
	friend ostream& operator<<(ostream& os, const VisitCard& VisitCard);

	//setters
	void setHostWorker(const string& hostWorker)
	{
		this->hostWorker = hostWorker;
	}

	// getters
	const string& getPurposeOfVisit() const { return purposeOfVisit; }
	const string& getVisitingDate() const { return visitingDate; }
	int getVisitCardNumber() const { return VisitCardNumber; }
	const Department& getDepartmentsToVisit() const { return departmentsToVisit; }
	const string& getHostWorker() const { return hostWorker; }

	virtual void toOs(ostream& os) const {};
};


#endif // !VisitCard__H_
