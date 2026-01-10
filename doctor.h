#ifndef DOCTOR_H
#define DOCTOR_H

#include "Worker.h"


class Doctor : public Worker {
    char* specialization;
public:

    // streaming
    friend ostream& operator<<(ostream& os, const Doctor& d);

    Doctor(const Worker& Worker);
    Doctor(const Doctor& other);
    Doctor(Doctor&& other);
    ~Doctor() { delete[] specialization; }

    // getters
    const char* getSpecialization() const { return specialization ? specialization : nullptr; };

    // setters
    bool setSpecialization(const char* specialization);

    // other methods

};

#endif // DOCTOR_H
