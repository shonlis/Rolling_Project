#pragma warning(disable: 4996)

#include "VisitCard.h"
#include "Worker.h"


int VisitCard::counter = 0;

VisitCard::VisitCard(const string& purposeOfVisit, const string& visitingDate, const Department& departmentsToVisit, const string& hostWorker)
    : departmentsToVisit(departmentsToVisit), VisitCardNumber(++counter)
{
	this->purposeOfVisit = purposeOfVisit;
	this->visitingDate = visitingDate;
	this->hostWorker = hostWorker;

}


ostream& operator<<(ostream& os, const VisitCard& VisitCard)
{
    os << "visit Details: \nvisit card number:" << VisitCard.getVisitCardNumber()
        << ", Purpose = " << VisitCard.getPurposeOfVisit()
        << ", Department = " << VisitCard.getDepartmentsToVisit().getName();
    if (!VisitCard.getHostWorker().empty()) {
        os << ", Host Worker Name = " << VisitCard.getHostWorker() << endl;
    }
    else {
        os << ", Host Worker Name = (none)" << endl;
    }
    return os;
}
