int Train::getLength() {
  if (!first) return 0;
  
  resetOpCount();
  Car* startCar = first;
  
  // Если лампочка выключена, включаем ее (это наш маркер)
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
        return steps; // Длина найдена
      } else {
        // Лампочка погашена - значит это не наш маркер
        steps = 0;
        current->light = true;
        countOp++; // операция изменения состояния
      }
    } else if (current->light) {
      // Нашли вагон с включенной лампочкой
      current->light = false;
      countOp++; // операция изменения состояния
      
      // Возвращаемся назад на steps шагов
      for (int i = 0; i < steps; i++) {
        current = current->prev;
        countOp++;
      }
      
      // Проверяем, вернулись ли мы в стартовый вагон
      if (current == startCar && !current->light) {
        // Лампочка погашена - значит это не наш маркер
        steps = 0;
        current->light = true;
        countOp++;
      }
      
      current = current->next;
      countOp++;
      steps = 0;
    } else {
      // Просто идем дальше
      current = current->next;
      countOp++;
    }
  }
}
