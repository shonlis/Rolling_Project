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
    const std::string& getPurposeOfVisit() const { return purposeOfVisit; }
    const std::string& getVisitingDate() const { return visitingDate; }
    int getVisitCardNumber() const { return VisitCardNumber; }
    const Department& getDepartmentsToVisit() const { return departmentsToVisit; }
    const std::string& getHostWorker() const { return hostWorker; }

private:
    std::string purposeOfVisit;
    std::string visitingDate;
    const Department& departmentsToVisit;
    std::string hostWorker;
};


#endif // !VisitCard__H_
