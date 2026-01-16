#include "Surgery.h"

Surgery::Surgery(const char* purposeOfVisit, const char* visitingDate, Department& departmentsToVisit, char* hostWorker, int surgeryRoomNumber, bool isFast) : VisitCard(purposeOfVisit, visitingDate, departmentsToVisit, hostWorker), surgeryRoomNumber(surgeryRoomNumber), isFast(isFast)
{}

void Surgery::setSurgeryRoomNumber(int surgeryRoomNumber)
{
	this->surgeryRoomNumber = surgeryRoomNumber;
}

void Surgery::setIsFast(bool isFast)
{
	this->isFast = isFast;
}
