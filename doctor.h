#ifndef DOCTOR_H
#define DOCTOR_H

#include "Worker.h"
#include <string>
#include <iostream>
using namespace std;

class Doctor : virtual public Worker
{
    std::string specialization;
public:

    Doctor(const char* name, int id, int birthYear, Gender gender, const char* specialization = nullptr);
    Doctor(const Doctor& other);
    Doctor(Doctor&& other) noexcept;
    ~Doctor() = default;

    // getters
    const char* getSpecialization() const { return specialization.c_str(); };

    // setters
    bool setSpecialization(const char* specialization);

    // other methods
    virtual void showthis() const
    {
        Worker::showthis();
        cout << "Specialization: " << (this->specialization.empty() ? "not defined" : this->specialization.c_str()) << endl;
    }
    virtual void toOs(ostream& os) const override;

};

#endif // DOCTOR_H
