#include <iostream>
using namespace std;
#include "VisitCard.h"

int VisitCard::counter = 0;

VisitCard::VisitCard(const char* purposeOfVisit, const char* visitingDate, Department& departmentsToVisit, Worker* hostWorker) : departmentsToVisit(departmentsToVisit), hostWorker(hostWorker), VisitCardNumber(++counter)
{
	this->purposeOfVisit = new char[strlen(purposeOfVisit) + 1];
	strcpy(this->purposeOfVisit, purposeOfVisit);

    strncpy(this->visitingDate, visitingDate, sizeof(this->visitingDate)-1);
    this->visitingDate[sizeof(this->visitingDate)-1] = '\0';
}


std::ostream& operator<<(std::ostream& os, const VisitCard& vc)
{
    os << "visit Details: \nvisit card number:" << vc.getVisitCardNumber()
       << ", Purpose = " << vc.getPurposeOfVisit()
       << ", Department = " << vc.getDepartmentsToVisit().getName();
    if (vc.getHostWorker()) {
        os << ", Host Worker Name = " << vc.getHostWorker()->getName();
    } else {
        os << ", Host Worker Name = (none)";
    }
    os << std::endl;
    return os;
}
