#include <iostream>
using namespace std;
#include "Worker.h"
#include "Person.h"

int Worker::counter = 0;

Worker::Worker(const char* name, int id, int birthYear, Gender gender) :
	Person(name, id, birthYear, gender), workerNumber(++counter) {}

Worker::Worker(const Person& person) : Person(person), workerNumber(++counter) {}

Worker::Worker(const Worker& worker) :Person(worker), workerNumber(worker.workerNumber) {}

Worker::Worker(Worker&& worker) : Person(move(worker)), workerNumber(worker.workerNumber) {}



