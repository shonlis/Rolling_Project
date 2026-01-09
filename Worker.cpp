#include <iostream>
using namespace std;
#include "Worker.h"

int Worker::counter = 0;

Worker::Worker(const Person& person) : Person(person), workerNumber(++counter) {}

Worker::Worker(const Worker& worker) :Person(worker), workerNumber(worker.workerNumber) {}

Worker::Worker(Worker&& worker) : Person(move(worker)), workerNumber(worker.workerNumber) {}



