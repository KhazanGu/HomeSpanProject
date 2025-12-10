#include <HomeSpan.h>
#include "StatusSwitch.h"
#include "Toggle.h"
#include <Wire.h>
#include <Adafruit_AHTX0.h>
#include "TempHumSensor.h"

constexpr char ssid[] = "Apple-Switch-TeHu";
constexpr char psd[] = "12345678";

const int statusPin = 27;
const int controlPin = 25;

const int togglePin = 26;

const int switchPin = 14;
const bool activeHigh = true;

const int SDAPin = 21;
const int SCLPin = 22;

// ------------------- StatusSwitch 实例 -------------------
StatusSwitch *statusSwitch;

// ------------------- AHT20 实例 -------------------
Adafruit_AHTX0 aht;
TempHumSensor *tempHum;

// ------------------- Setup -------------------
void setup() {
//  Serial.begin(115200);
//  homeSpan.setLogLevel(1);
  
  homeSpan.setApSSID(ssid);
  homeSpan.setApPassword(psd);
  homeSpan.setStatusPin(statusPin);
  homeSpan.setControlPin(controlPin);
  homeSpan.setStatusAutoOff(120);
  homeSpan.enableAutoStartAP();

  // 初始化 HomeSpan
  homeSpan.begin(Category::Switches, "Switch");
  
  // ----------------- 开关模块 -----------------
  new SpanAccessory();  
      statusSwitch = new StatusSwitch(switchPin, activeHigh);
      new Toggle(togglePin, &statusSwitch);
  
  // ----------------- 温湿度传感器模块 -----------------
  tempHum = new TempHumSensor();  // Service::TemperatureSensor / HumiditySensor 内部会显示传感器图标
  
  // StatusSwitch
  pinMode(switchPin, OUTPUT);
  if (activeHigh) digitalWrite(switchPin, LOW);
  else digitalWrite(switchPin, HIGH);

  // TempHumSensor
  Wire.begin(SDAPin, SCLPin);

  Serial.println("Initializing AHT20 sensor...");
  if (!aht.begin()) {
    Serial.println("Failed to find AHT20 sensor! Check wiring.");
    while (1);
  }
  Serial.println("AHT20 sensor initialized.");

}

// ------------------- 主循环 -------------------
void loop() {
  homeSpan.poll();
  tempHum->loop();  // 定期更新温湿度
}
