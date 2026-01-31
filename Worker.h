#ifndef Worker__H_
#define Worker__H_
#include "Person.h"

class Worker : public Person
{
protected:
    const int workerNumber;
    static int counter;
    Worker(const string name, int id, int birthYear, Gender gender);
    Worker(const Worker& worker);


public:

    virtual void showthis() const = 0 {
        Person::showthis();
        cout << "Worker Number: " << workerNumber << endl;
    }

    void operator=(const Worker& worker) = delete;
    void operator=(const Worker&& worker) = delete;

    virtual void toOs(ostream& os) const override
    { os << "Worker Number: " << workerNumber << endl; }

};


#endif // !Worker__H_
