// Copyright 2021 NNTU-CS
#include "train.h"
#include <algorithm>

Train::Train() : first(nullptr), countOp(0), length(0) {}

Train::~Train() {
  if (!first) return;
  Car* current = first;
  do {
    Car* next = current->next;
    delete current;
    current = next;
  } while (current != first);
}
void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    first = newCar;
    first->next = first;
    first->prev = first;
  } else {
    Car* last = first->prev;
    last->next = newCar;
    newCar->prev = last;
    newCar->next = first;
    first->prev = newCar;
  }
  length++;
}
int Train::getLength() {
  if (!first) return 0;
  resetOpCount();
  Car* startCar = first;
  if (!startCar->light) {
    startCar->light = true;
    countOp++; // учитываем операцию изменения состояния
  }
  int steps = 0;
  Car* current = startCar->next;
  countOp++; // переход в следующий вагон
  while (true) {
    steps++;
    if (current == startCar) {
            // Если вернулись в стартовый вагон
      if (current->light) {
                // Если лампочка все еще горит - значит это наш маркер
                // и мы сделали полный круг
        return steps;
      } else {
        steps = 0;
        current->light = true;
        countOp++;
      }
    } else if (current->light) {
      current->light = false;
      countOp++; // операция изменения состояния
      for (int i = 0; i < steps; i++) {
        current = current->prev;
        countOp++;
      } // Проверяем, вернулись ли мы в стартовый вагон
      if (current == startCar) {
        steps = 0;
        current->light = true;
        countOp++;
      }
      current = current->next;
      countOp++;
      steps = 0;
    } else {
      current = current->next;
      countOp++;
    }
  }
}
int Train::getOpCount() const {
  return countOp;
}
int Train::getActualLength() const {
  return length;
}
void Train::resetOpCount() {
  countOp = 0;
}
Train Train::createAllLightsOn(int n) {
  Train train;
  for (int i = 0; i < n; i++) {
    train.addCar(true);
  }
  return train;
}
Train Train::createAllLightsOff(int n) {
  Train train;
  for (int i = 0; i < n; i++) {
    train.addCar(false);
  }
  return train;
}
Train Train::createRandomLights(int n) {
  Train train;
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> distrib(0, 1);
  for (int i = 0; i < n; i++) {
    train.addCar(distrib(gen) == 1);
  }
  return train;
}
