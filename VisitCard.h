#pragma once

#include "department.h"
#include "Worker.h"

class VisitCard
{
private:
	char* purposeOfVisit;
	char* visitingDate;
	department& departmentsToVisit;
	Worker& hostWorker;
};

