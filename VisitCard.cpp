#pragma warning(disable: 4996)
#include <iostream>
using namespace std;
#include "VisitCard.h"
#include "Worker.h"

int VisitCard::counter = 0;

VisitCard::VisitCard(const char* purposeOfVisit, const char* visitingDate, Department& departmentsToVisit, Worker* hostWorker) : departmentsToVisit(departmentsToVisit), hostWorker(hostWorker), VisitCardNumber(++counter)
{
    this->purposeOfVisit = new char[strlen(purposeOfVisit) + 1];
    strcpy(this->purposeOfVisit, purposeOfVisit);

    strncpy(this->visitingDate, visitingDate, sizeof(this->visitingDate) - 1);
    this->visitingDate[sizeof(this->visitingDate) - 1] = '\0';
}
ostream& operator<<(ostream& os, const VisitCard& vc)
{
     os << "visit Details: \nvisit card number:" << vc.getVisitCardNumber()
        << ", Purpose = " << vc.getPurposeOfVisit()
        << ", Department = " << vc.getDepartmentsToVisit().getName();
    if (vc.getHostWorker()) {
        os << ", Host Worker Name = " << vc.getHostWorker() << endl;
    }
    else {
        os << ", Host Worker Name = (none)" << endl;
    }
    return os;
}