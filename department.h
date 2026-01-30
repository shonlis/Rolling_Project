#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <vector>

class Doctor;
class Nurse;
class Visitor;

class Department {
    std::string name;
    std::vector<Doctor*> doctors;
    std::vector<Nurse*> nurses;
    std::vector<Visitor*> visitors;

public:
    Department(const string name = "none");
    ~Department();

    // getters
    const string getName() const { return name.c_str(); };
    int getCurrentNumberOfDoctors() const { return static_cast<int>(doctors.size()); }
    int getCurrentNumberOfNurses() const { return static_cast<int>(nurses.size()); }
    int getCurrentNumberOfVisitors() const { return static_cast<int>(visitors.size()); }

    const std::vector<Doctor*>& getDoctors() const { return doctors; }
    const std::vector<Nurse*>& getNurses() const { return nurses; }
    const std::vector<Visitor*>& getVisitors() const { return visitors; }

    //setters
    void setName(const string name);

    // operators
    Department& operator+=(Doctor& doctor);
    Department& operator+=(Nurse& nurse);

    // other methods
    bool addDoctor(Doctor* doctor);
    bool DoctorExist(const Doctor& doctor);

    bool addNurse(Nurse* nurse);
    bool NurseExist(const Nurse& nurse);
    
    bool addVisitor(Visitor* visitor);
    bool VisitorExist(const Visitor& visitor);

    void printDoctors() const;
    void printNurses() const;

};

#endif // DEPARTMENT_H
