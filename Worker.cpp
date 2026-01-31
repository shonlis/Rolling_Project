#include "Worker.h"

int Worker::counter = 0;

Worker::Worker(const string name, int id, int birthYear, Gender gender) :Person(name, id, birthYear, gender), workerNumber(++counter) {}

Worker::Worker(const Worker& worker): Worker(worker.getName(), worker.getId(), worker.getBirthYear(), worker.getGender())
{}

