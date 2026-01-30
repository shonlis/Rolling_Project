#include <iostream>
using namespace std;

#include "Surgery.h"

Surgery::Surgery(const std::string& purposeOfVisit, const std::string& visitingDate, Department& departmentsToVisit, const std::string& hostWorker, int surgeryRoomNumber, bool isFast)
    : VisitCard(purposeOfVisit, visitingDate, departmentsToVisit, hostWorker), surgeryRoomNumber(surgeryRoomNumber), isFast(isFast) {}

void Surgery::setSurgeryRoomNumber(int surgeryRoomNumber)
{
	this->surgeryRoomNumber = surgeryRoomNumber;
}

void Surgery::setIsFast(bool isFast)
{
	this->isFast = isFast;
}

void Surgery::toOs(ostream& os) const
{
	VisitCard::toOs(os);
	os << "Surgery Room Number: " << surgeryRoomNumber << endl;
	os << "Is Fast Surgery: " << (isFast ? "Yes" : "No") << endl;
}

std::unique_ptr<VisitCard> Surgery::clone() const
{
    return std::make_unique<Surgery>(*this);
}