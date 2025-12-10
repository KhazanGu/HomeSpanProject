#include <HomeSpan.h>
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include "TempHumSensor.h"

// ------------------- AHT20 实例 -------------------
Adafruit_AHTX0 aht;

// ------------------- Setup -------------------
void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  Serial.println("Initializing AHT20 sensor...");
  if (!aht.begin()) {
    Serial.println("Failed to find AHT20 sensor! Check wiring.");
    while (1);
  }
  Serial.println("AHT20 sensor initialized.");

  homeSpan.setLogLevel(1);
  homeSpan.setApSSID("Apple-temperature");
  homeSpan.setApPassword("12345678");
  homeSpan.setStatusPin(18);
  homeSpan.setControlPin(19);
  homeSpan.enableAutoStartAP();
  
  homeSpan.begin(Category::Sensors, "Temperature Humidity Sensor");

  // 设备信息
  new SpanAccessory();
  new Service::AccessoryInformation();
  new Characteristic::Name("AHT20 Sensor");
  new Characteristic::Manufacturer("DIY");
  new Characteristic::Model("AHT20-HS");
  new Characteristic::SerialNumber("001");
  new Characteristic::FirmwareRevision("1.0");
  new Characteristic::Identify();

  // 添加温湿度传感器
  new TempHumSensor();
}

// ------------------- 主循环 -------------------
void loop() {
  homeSpan.poll();
}
