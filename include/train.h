#ifndef INCLUDE_TRAIN_H_
#define INCLUDE_TRAIN_H_

class Train {
 private:
  struct Car {
    bool light; // состояние лампочки
    Car *next;
    Car *prev;
  };

  int countOp; // счетчик шагов (число переходов из вагона в вагон)
  int length;
  Car *first; // точка входа в поезд (первый вагон)
 public:
  Train();
  ~Train();

  void addCar(bool light); // добавить вагон с начальным состоянием лампочки
  int getLength();          // вычислить длину поезда
  int getOpCount() const;   // вернуть число переходов (из вагона в вагон)
  int getActualLength() const;
  void resetOpCount();

  static Train createAllLightsOn(int n);
  static Train createAllLightsOff(int n);
  static Train createRandomLights(int n);
};
#endif  // INCLUDE_TRAIN_H_
