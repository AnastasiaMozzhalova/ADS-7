// Copyright 2021 NNTU-CS
#include "train.h"
#include <cstdlib>

Train::Train() : operationsCount(0), firstCar(nullptr) {}

void Train::addCar(bool isLightOn) {
  Car* newCar = new Car{isLightOn, nullptr, nullptr};

  if (!firstCar) {
    firstCar = newCar;
    newCar->nextCar = newCar;
    newCar->prevCar = newCar;
  } else {
    Car* lastCar = firstCar->prevCar;
    newCar->nextCar = firstCar;
    newCar->prevCar = lastCar;
    lastCar->nextCar = newCar;
    firstCar->prevCar = newCar;
    firstCar = newCar;
  }
}

int Train::getLength() {
  if (!firstCar) return 0;
  if (firstCar->nextCar == firstCar) return 1;

  operationsCount = 0;
  Car* currentCar = firstCar;
  int trainSize = 1;

  if (!currentCar->light) {
    currentCar->light = true;
  }

  currentCar = currentCar->nextCar;
  operationsCount += 2;

  while (!currentCar->light) {
    currentCar = currentCar->nextCar;
    operationsCount += 2;
    trainSize++;
  }

  currentCar->light = false;

  if (!firstCar->light) {
    return trainSize;
  }

  while (true) {
    currentCar = firstCar;
    trainSize = 1;

    if (!currentCar->light) {
      currentCar->light = true;
    }

    currentCar = currentCar->nextCar;
    operationsCount += 2;

    while (!currentCar->light) {
      currentCar = currentCar->nextCar;
      operationsCount += 2;
      trainSize++;
    }

    currentCar->light = false;

    if (!firstCar->light) {
      return trainSize;
    }
  }
}

int Train::getOpCount() {
  return operationsCount;
}

Train::~Train() {
  if (!firstCar) return;

  if (firstCar->nextCar == firstCar) {
    delete firstCar;
    firstCar = nullptr;
    return;
  }

  Car* current = firstCar->nextCar;
  while (current != firstCar) {
    Car* tempCar = current;
    current = current->nextCar;
    delete tempCar;
  }

  delete firstCar;
  firstCar = nullptr;
}
