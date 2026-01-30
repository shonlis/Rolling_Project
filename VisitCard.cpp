#pragma warning(disable: 4996)
#include <iostream>
using namespace std;
#include "VisitCard.h"
#include "Worker.h"


int VisitCard::counter = 0;

VisitCard::VisitCard(const std::string& purposeOfVisit, const std::string& visitingDate, const Department& departmentsToVisit, const std::string& hostWorker)
    : VisitCardNumber(++counter), purposeOfVisit(purposeOfVisit), visitingDate(visitingDate), departmentsToVisit(departmentsToVisit), hostWorker(hostWorker)
{
}

// Copy ctor: preserve VisitCardNumber
VisitCard::VisitCard(const VisitCard& other)
    : VisitCardNumber(other.VisitCardNumber), departmentsToVisit(other.departmentsToVisit), purposeOfVisit(other.purposeOfVisit), visitingDate(other.visitingDate), hostWorker(other.hostWorker)
{
}

std::ostream& operator<<(std::ostream& os, const VisitCard& vc)
{
    os << "visit Details: \nvisit card number:" << vc.getVisitCardNumber()
        << ", Purpose = " << vc.getPurposeOfVisit()
        << ", Department = " << vc.getDepartmentsToVisit().getName();
    if (!vc.getHostWorker().empty()) {
        os << ", Host Worker Name = " << vc.getHostWorker() << endl;
    }
    else {
        os << ", Host Worker Name = (none)" << endl;
    }
    vc.toOs(os);
    return os;
}

// destructor defined in header as = default
