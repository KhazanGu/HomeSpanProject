#pragma once
#include <HomeSpan.h>

class StatusSwitch : public Service::Switch {
public:
  StatusSwitch(int pin, bool activeHigh)
    : Service::Switch(), pin(pin), activeHigh(activeHigh) {

    pinMode(pin, OUTPUT);
    power = new Characteristic::On(0);
  }

  boolean update() override {
    bool v = power->getNewVal();

    digitalWrite(pin, activeHigh ? (v ? HIGH : LOW)
                                 : (v ? LOW : HIGH));

    Serial.printf("[HomeKit] StatusSwitch -> %d\n", v);
    return true;
  }

  void toggleByButton() {
    bool newVal = !power->getVal();
    power->setVal(newVal);

    Serial.printf("[Toggle] StatusSwitch -> %d\n", newVal);

    update();  // 立即更新 GPIO
  }

private:
  int pin;
  bool activeHigh;
  SpanCharacteristic *power;
};
