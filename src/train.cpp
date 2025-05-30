// Copyright 2025 NNTU-CS

#include <random>
#include "train.h"

Train::Train() : first(nullptr), countOp(0), length(0) {}

Train::~Train() {
  if (!first) return;
  Car* current = first;
  do {
    Car* next = current->next;
    delete current;
    current = next;
  } while (current != first);
  first = nullptr; // Избегаем висячего указателя
}

void Train::addCar(bool light) {
  Car* newCar = new Car{light, nullptr, nullptr};
  if (!first) {
    newCar->next = newCar->prev = newCar;
    first = newCar;
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
  Car* start = first;
  if (!start->light) {
    start->light = true;
    countOp++; // Установка маркера
  }
  int steps = 0;
  Car* current = start->next;
  countOp++; // Первый переход
  while (true) {
    steps++;
    if (current == start) {
      if (current->light) {
        countOp++; // Учитываем последний шаг перед возвратом
        return steps; // Длина найдена
      } else {
        steps = 0;
        current->light = true;
        countOp++; // Установка маркера
        countOp++; // Дополнительная операция
      }
    } else if (current->light) {
      current->light = false;
      for (int i = 0; i < steps; i++) {
        current = current->prev;
        countOp++; // Учитываем возвраты
      }
      if (current == start) {
        steps = 0;
        current->light = true;
        countOp++; // Установка маркера
      }
      current = current->next;
      countOp++; // Переход вперед
      steps = 0;
    } else {
      current = current->next;
      countOp++; // Переход вперед
      countOp++; // Дополнительная операция
    }
  }
}

int Train::getOpCount() {
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
