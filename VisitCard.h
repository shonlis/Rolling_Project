#ifndef VisitCard__H_
#define VisitCard__H_
#pragma warning(disable: 4996)

#include <string>
#include <iostream>
#include "Department.h"

class VisitCard
{
public:
    const int VisitCardNumber;
    static int counter;
    
    VisitCard(const std::string& purposeOfVisit, const std::string& visitingDate, const Department& departmentsToVisit, const std::string& hostWorker);
    
    // allow copying - preserve VisitCardNumber
    VisitCard(const VisitCard& other);

    virtual ~VisitCard() = default;

    // disable assignment
    VisitCard& operator=(const VisitCard&) = delete;

    //operators overloading
    virtual void toOs(std::ostream& os) const {}
    friend std::ostream& operator<<(std::ostream& os, const VisitCard& VisitCard);

    //setters
    void setHostWorker(const std::string& hostWorker)
    {
        this->hostWorker = hostWorker;
    }

    // getters
    const char* getPurposeOfVisit() const { return purposeOfVisit.c_str(); }
    const char* getVisitingDate() const { return visitingDate.c_str(); }
    int getVisitCardNumber() const { return VisitCardNumber; }
    const Department& getDepartmentsToVisit() const { return departmentsToVisit; }
    const char* getHostWorker() const { return hostWorker.empty() ? nullptr : hostWorker.c_str(); }

private:
    std::string purposeOfVisit;
    std::string visitingDate;
    const Department& departmentsToVisit;
    std::string hostWorker;
};


#endif // !VisitCard__H_
