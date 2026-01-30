#pragma warning(disable: 4996)
#include <iostream>
using namespace std;
#include "Department.h"
#include "Doctor.h"
#include "Nurse.h"
#include "Visitor.h"

Department::Department(const char* name) : name(name ? name : std::string("none")) {}

Department::~Department()
{
    // Department does not own Doctor/Nurse/Visitor objects; only clears its lists
    doctors.clear();
    nurses.clear();
    visitors.clear();
}

bool Department::addDoctor(Doctor* doctor)
{
    if (!doctor) return false;
    if (DoctorExist(*doctor)) return false;
    doctors.push_back(doctor);
    return true;
}

bool Department::DoctorExist(const Doctor& doctor)
{
    for (auto d : doctors) if (d && d->getId() == doctor.getId()) return true;
    return false;
}

bool Department::addNurse(Nurse* nurse)
{
    if (!nurse) return false;
    if (NurseExist(*nurse)) return false;
    nurses.push_back(nurse);
    return true;
}

bool Department::NurseExist(const Nurse& nurse)
{
    for (auto n : nurses) if (n && n->getId() == nurse.getId()) return true;
    return false;
}

bool Department::addVisitor(Visitor* visitor)
{
    if (!visitor) return false;
    if (VisitorExist(*visitor)) return false;
    visitors.push_back(visitor);
    return true;
}

bool Department::VisitorExist(const Visitor& visitor)
{
    for (auto v : visitors) if (v && v->getId() == visitor.getId()) return true;
    return false;
}

void Department::printDoctors() const
{
    for (size_t i = 0; i < doctors.size(); ++i) {
        cout << doctors[i]->getName();
        if (i + 1 < doctors.size()) cout << ", ";
    }
    cout << endl;
}

void Department::printNurses() const 
{
    for (size_t i = 0; i < nurses.size(); ++i) {
        cout << nurses[i]->getName();
        if (i + 1 < nurses.size()) cout << ", ";
    }
    cout << endl;
}

Department& Department::operator+=(Nurse& nurse)
{
    addNurse(&nurse);
    return *this;
}

Department& Department::operator+=(Doctor& doctor)
{
    addDoctor(&doctor);
    return *this;
}

void Department::setName(const char* name)
{
    this->name = name ? name : std::string();
}

/******************************************************************************/
