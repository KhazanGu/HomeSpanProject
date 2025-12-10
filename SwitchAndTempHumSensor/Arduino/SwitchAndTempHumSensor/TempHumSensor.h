#pragma once
#include <HomeSpan.h>
#include <Adafruit_AHTX0.h>

extern Adafruit_AHTX0 aht;

struct TempHumSensor {
  SpanCharacteristic *tempChar;
  SpanCharacteristic *humChar;

  Service::TemperatureSensor *tempService;
  Service::HumiditySensor *humService;

  TempHumSensor() {
    new SpanAccessory();

    new Service::AccessoryInformation();
      new Characteristic::Name("TempHum Sensor");
      new Characteristic::Manufacturer("Khazan");
      new Characteristic::Model("AHT20");
      new Characteristic::SerialNumber("TH-001");
      new Characteristic::Identify();

    tempService = new Service::TemperatureSensor();
    tempChar = new Characteristic::CurrentTemperature(0);

    humService = new Service::HumiditySensor();
    humChar = new Characteristic::CurrentRelativeHumidity(0);
  }

  void loop() {
    static unsigned long lastRead = 0;
    if (millis() - lastRead > 5000) {
      lastRead = millis();
      sensors_event_t humEvent, tempEvent;

      if (aht.getEvent(&humEvent, &tempEvent)) {
          float humidity = humEvent.relative_humidity;
          float temperature = tempEvent.temperature;
      
          tempChar->setVal(temperature);
          humChar->setVal(humidity);
      
          LOG1("Temp: "); LOG1(temperature);
          LOG1(" °C | Hum: "); LOG1(humidity); LOG1(" %\n");
      } else {
          LOG1("AHT20 read failed\n");
      }
    }
  }
};
