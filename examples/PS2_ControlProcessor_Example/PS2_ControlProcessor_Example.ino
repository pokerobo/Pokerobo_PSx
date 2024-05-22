#include "Pokerobo_PSx.h"

class DemoControlProcessor: public PS2ControlProcessor {
  public:
    virtual void processStartButtonPressedEvent();
    virtual void processSelectButtonPressedEvent();
    virtual void processAnalogButtonPressedEvent();
    virtual void processDPadUpButtonPressedEvent();
    virtual void processDPadRightButtonPressedEvent();
    virtual void processDPadDownButtonPressedEvent();
    virtual void processDPadLeftButtonPressedEvent();
    virtual void processLeftJoystickChangeEvent(int nJoyX, int nJoyY);
    virtual void processRightJoystickChangeEvent(int nJoyX, int nJoyY);
};

PS2Listener ps2Controller;
DemoControlProcessor ps2Processor;

void setup() {
  Serial.begin(57600);
  ps2Controller.set(&ps2Processor);
  ps2Controller.begin();
}

void loop() {
  uint32_t begin = millis();
  ps2Controller.loop();
  delay(max(200 + begin - millis(), 0));
}

void DemoControlProcessor::processStartButtonPressedEvent() {
  Serial.println("Console: processStartButtonPressedEvent");
}

void DemoControlProcessor::processSelectButtonPressedEvent() {
  Serial.println("Console: processSelectButtonPressedEvent");
}

void DemoControlProcessor::processAnalogButtonPressedEvent() {
  Serial.println("Console: processAnalogButtonPressedEvent");
}

void DemoControlProcessor::processDPadUpButtonPressedEvent() {
  Serial.println("Console: processDPadUpButtonPressedEvent");
}

void DemoControlProcessor::processDPadRightButtonPressedEvent() {
  Serial.println("Console: processDPadRightButtonPressedEvent");
}

void DemoControlProcessor::processDPadDownButtonPressedEvent() {
  Serial.println("Console: processDPadDownButtonPressedEvent");
}

void DemoControlProcessor::processDPadLeftButtonPressedEvent() {
  Serial.println("Console: processDPadLeftButtonPressedEvent");
}

void DemoControlProcessor::processLeftJoystickChangeEvent(int nJoyX, int nJoyY) {
  Serial.print("Console: leftJoystick - "),
    Serial.print(nJoyX), Serial.print(", "), Serial.println(nJoyY);
}

void DemoControlProcessor::processRightJoystickChangeEvent(int nJoyX, int nJoyY) {
  Serial.print("Console: rightJoystick - "),
    Serial.print(nJoyX), Serial.print(", "), Serial.println(nJoyY);
}
