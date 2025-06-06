// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
  int operationsCount;
  struct Car {
    bool light;
    Car* nextCar;
    Car* prevCar;
  };
  Car* firstCar;

 public:
  Train();
  void addCar(bool isLightOn);
  int getLength();
  int getOpCount();
  ~Train();
};

#endif  // INCLUDE_TRAIN_H_
