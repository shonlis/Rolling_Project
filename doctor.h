#ifndef DOCTOR_H
#define DOCTOR_H

#include "Worker.h"
#include <string>
#include <iostream>
using namespace std;

class Doctor : virtual public Worker
{
    string specialization;
public:

    Doctor(const string& name, int id, int birthYear, Gender gender, const string& specialization = "there isn't");
    Doctor(const Doctor& doctor);
    Doctor(Doctor&& doctor) = delete;

    // getters
    const string& getSpecialization() const { return specialization; };

    // setters
    bool setSpecialization(const string& specialization);

    // other methods
    virtual void showthis() const
    {
        Worker::showthis();
        cout << "Specialization: " << (this->specialization.empty() ? "not defined" : this->specialization) << endl;
    }
    virtual void toOs(ostream& os) const override;

};

#endif // DOCTOR_H
