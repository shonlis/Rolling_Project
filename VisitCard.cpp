#include <iostream>
using namespace std;
#include "VisitCard.h"

int VisitCard::counter = 0;

VisitCard::VisitCard(const char* purposeOfVisit, const char* visitingDate, department& departmentsToVisit, Worker* hostWorker) : departmentsToVisit(departmentsToVisit), hostWorker(hostWorker), VisitCardNumber(++counter)
{
	this->purposeOfVisit = new char[strlen(purposeOfVisit) + 1];
	strcpy(this->purposeOfVisit, purposeOfVisit);

	strcpy(this->visitingDate, visitingDate);
}


ostream& operator<<(ostream& os, const VisitCard& VisitCard)
{
	os << "visit Details: \nvisit card number:" << VisitCard.getVisitCardNumber() << ", Purpose = " << VisitCard.getPurposeOfVisit() << ", Department = " << VisitCard.getDepartmentsToVisit().getName() << ", Host Worker Name = " << VisitCard.getHostWorker()->getName() << endl;
	return os;
}
