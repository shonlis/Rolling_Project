#ifndef DOCTOR_H
#define DOCTOR_H

#include "Worker.h"
#include <string>

class Doctor : public Worker {
public:
    char* specialization;

    // streaming
    friend std::ostream& operator<<(std::ostream& os, const Doctor& d);

    Doctor(const Worker& Worker);
    Doctor(const Doctor& other);
    ~Doctor();

    // getters
    const char* getSpecialization() const { return specialization ? specialization : nullptr; };

    // setters
    bool setSpecialization(const char* specialization);

    // other methods

};

#endif // DOCTOR_H
