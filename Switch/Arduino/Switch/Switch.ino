#include "HomeSpan.h" 
#include "StatusSwitch.h"     
#include "Toggle.h"     

constexpr char ssid[] = "Apple-Switch";
constexpr char psd[] = "12345678";

const int statusPin = 18;
const int controlPin = 19;

const int togglePin = 17;
const int switchPin = 14;

const bool activeHigh = true;

StatusSwitch *statusSwitch;

void setup() {

//  Serial.begin(115200);

  homeSpan.setApSSID(ssid);
  homeSpan.setApPassword(psd);
  homeSpan.setStatusPin(statusPin);
  homeSpan.setControlPin(controlPin);
  homeSpan.setStatusAutoOff(120);
  homeSpan.enableAutoStartAP();

  homeSpan.begin(Category::Switches,"Switch");

  new SpanAccessory();                                                          
      statusSwitch = new StatusSwitch(switchPin, activeHigh);
      new Toggle(togglePin, &statusSwitch);

  pinMode(switchPin, OUTPUT);
  if (activeHigh) digitalWrite(switchPin, LOW);
  else digitalWrite(switchPin, HIGH);
  
}


void loop(){
  homeSpan.poll();
}



  
