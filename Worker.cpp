

#include "Worker.h"
#include <ostream>
using namespace std;

int Worker::counter = 0;

Worker::Worker(const string name, int id, int birthYear, Gender gender) :Person(name, id, birthYear, gender), workerNumber(++counter) {}

Worker::Worker(const Person& person) : Person(person), workerNumber(++counter) {}

Worker::Worker(const Worker& worker) :Person(worker), workerNumber(worker.workerNumber) {}

Worker::Worker(Worker&& worker) noexcept : Person(std::move(worker)), workerNumber(worker.workerNumber) {}



