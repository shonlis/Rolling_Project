#ifndef DOCTOR_H
#define DOCTOR_H

#include "Worker.h"


class Doctor : virtual public Worker
{
    char* specialization;
public:

    Doctor(const char* name, int id, int birthYear, Gender gender, const char* specialization = nullptr);

    Doctor(const Worker& Worker);
    Doctor(const Doctor& other);
    Doctor(Doctor&& other);
    ~Doctor() { delete[] specialization; }

    // getters
    const char* getSpecialization() const { return specialization ? specialization : nullptr; };

    // setters
    bool setSpecialization(const char* specialization);

    // other methods
    virtual void showthis() const override{
        Worker::showthis();
		cout << "Specialization: " << (specialization ? specialization : "not defined") << endl;
    }
    virtual void toOs(ostream& os) const override;

};

#endif // DOCTOR_H
