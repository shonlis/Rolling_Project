#include <iostream>
using namespace std;
#include "Worker.h"

/*NOTE:
* 1. created copy c'tor for Researcher.
* 2. created move c'tor for Researcher and we must call to Person move c'tor otherwise we will call the default Person c'tor.
* 3. 
*/

int Worker::counter = 0;

Worker::Worker(const Person& person) : Person(person), workerNumber(++counter) {}

Worker::Worker(const Worker& worker) :Person(worker.getName(), worker.getId(), worker.getBirthYear(), worker.getGender()), workerNumber(worker.workerNumber) {}

Worker::Worker(Worker&& worker) : workerNumber(worker.workerNumber), Person(std::move(worker)){}



