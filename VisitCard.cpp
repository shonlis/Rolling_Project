#pragma warning(disable: 4996)
#include <iostream>
using namespace std;
#include "VisitCard.h"
#include "Worker.h"


int VisitCard::counter = 0;

VisitCard::VisitCard(const char* purposeOfVisit, const char* visitingDate, Department& departmentsToVisit, char* hostWorker)
    : departmentsToVisit(departmentsToVisit), hostWorker(nullptr), VisitCardNumber(++counter)
{
    if (purposeOfVisit)
    {
        this->purposeOfVisit = new char[strlen(purposeOfVisit) + 1];
        strcpy(this->purposeOfVisit, purposeOfVisit);
    }
    else
    {
        this->purposeOfVisit = nullptr;
    }

    if (visitingDate)
    {
        strncpy(this->visitingDate, visitingDate, sizeof(this->visitingDate) - 1);
        this->visitingDate[sizeof(this->visitingDate) - 1] = '\0';
    }
    else
    {
        this->visitingDate[0] = '\0';
    }

    if (hostWorker)
    {
        size_t len = strlen(hostWorker) + 1;
        this->hostWorker = new char[len];
        strncpy(this->hostWorker, hostWorker, len);
        this->hostWorker[len - 1] = '\0';
    }
    else
    {
        this->hostWorker = nullptr;
    }
}

// Copy ctor: create a deep copy and preserve VisitCardNumber from original
VisitCard::VisitCard(const VisitCard& other)
    : VisitCardNumber(other.VisitCardNumber), departmentsToVisit(other.departmentsToVisit), hostWorker(nullptr)
{
    if (other.purposeOfVisit)
    {
        size_t len = strlen(other.purposeOfVisit) + 1;
        purposeOfVisit = new char[len];
        strncpy(purposeOfVisit, other.purposeOfVisit, len);
        purposeOfVisit[len - 1] = '\0';
    }
    else
    {
        purposeOfVisit = nullptr;
    }

    strncpy(this->visitingDate, other.visitingDate, sizeof(this->visitingDate));
    this->visitingDate[sizeof(this->visitingDate) - 1] = '\0';

    if (other.hostWorker)
    {
        size_t len = strlen(other.hostWorker) + 1;
        this->hostWorker = new char[len];
        strncpy(this->hostWorker, other.hostWorker, len);
        this->hostWorker[len - 1] = '\0';
    }
    else
    {
        this->hostWorker = nullptr;
    }
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
	vc.toOs(os);
    return os;
}
 
VisitCard::~VisitCard()
{
    if (purposeOfVisit)
    {
        delete[] purposeOfVisit;
    }
    if (hostWorker)
    {
        delete[] hostWorker;
    }
}
