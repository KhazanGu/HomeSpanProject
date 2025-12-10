#pragma once
#include <HomeSpan.h>
#include <Adafruit_AHTX0.h>

// 外部声明 AHT20 实例
extern Adafruit_AHTX0 aht;

struct TempHumSensor : Service::TemperatureSensor {

  SpanCharacteristic *tempChar;
  SpanCharacteristic *humChar;

  TempHumSensor() : Service::TemperatureSensor() {
    tempChar = new Characteristic::CurrentTemperature(0);
    auto *humService = new Service::HumiditySensor();
    humChar = new Characteristic::CurrentRelativeHumidity(0);
  }

  void loop() override {
    static unsigned long lastRead = 0;

    if (millis() - lastRead > 5000) {  // 每 5 秒读取一次
      lastRead = millis();

      sensors_event_t humidity, temp;
      if (aht.getEvent(&humidity, &temp)) {

        // 更新 HomeKit 特征值（HomeSpan 2.x）
        tempChar->setVal(temp.temperature);
        humChar->setVal(humidity.relative_humidity);

        // 串口打印
        LOG1("Temp: "); LOG1(temp.temperature);
        LOG1(" °C | Hum: "); LOG1(humidity.relative_humidity); LOG1(" %\n");
      } else {
        LOG1("AHT20 read failed\n");
      }
    }
  }
};
