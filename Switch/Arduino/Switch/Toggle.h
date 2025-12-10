#pragma once
#include <HomeSpan.h>
#include "StatusSwitch.h"

class Toggle : public Service::AccessoryInformation {
public:
  Toggle(int pin, StatusSwitch **switchRef)
    : pin(pin), switchRef(switchRef) {

    new Characteristic::Name("Switch");
    new Characteristic::Manufacturer("Khazan");
    new Characteristic::Model("SS-01");
    new Characteristic::SerialNumber("001");
    identify = new Characteristic::Identify();

    new SpanButton(pin);  // 使用默认触发模式，按下触发
  }

  void button(int pin, int pressType) override {
    // 单击按钮时切换开关
    if (pin == this->pin && pressType == SpanButton::SINGLE) {
      if (*switchRef != nullptr) {
        (*switchRef)->toggleByButton();
      }
    }
  }

private:
  int pin;
  StatusSwitch **switchRef;
  Characteristic::Identify *identify;
};
