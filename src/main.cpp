// Copyright 2025 NNTU-CS
#include "train.h"
#include <chrono>
#include <cstdint>
#include <iostream>
#include <random>
#include <vector>
#include "train.h"

void testTrain(int n, int mode, int& steps, int64_t& micros) {
  Train train;
  if (mode == 0) train = Train::createAllLightsOff(n);
  else if (mode == 1) train = Train::createAllLightsOn(n);
  else train = Train::createRandomLights(n);

  auto start = std::chrono::high_resolution_clock::now();
  [[maybe_unused]] int len = train.getLength();
  auto end = std::chrono::high_resolution_clock::now();

  auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
  micros = duration.count();
  steps = train.getOpCount();
}

int main() {
  std::cout << "Длина, Режим, Шаги, Время (в микросекундах)\n";

  for (int n = 10; n <= 100; n += 10) {
    for (int mode = 0; mode <= 2; ++mode) {
      int steps;
      int64_t micros;
      testTrain(n, mode, steps, micros);
      std::cout << n << "," << mode << "," << steps << "," << micros << "\n";
    }
  }

  return 0;
}
