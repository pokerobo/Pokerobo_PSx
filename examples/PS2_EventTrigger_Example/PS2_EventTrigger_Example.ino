#include "Pokerobo_PSx.h"

void onStartButtonPressed() {
  Serial.println("Console: onStartButtonPressed");
}

void onSelectButtonPressed() {
  Serial.println("Console: onSelectButtonPressed");
}

void onAnalogButtonPressed() {
  Serial.println("Console: onAnalogButtonPressed");
}

void onDPadUpButtonPressed() {
  Serial.println("Console: onDPadUpButtonPressed");
}

void onDPadRightButtonPressed() {
  Serial.println("Console: onDPadRightButtonPressed");
}

void onDPadDownButtonPressed() {
  Serial.println("Console: onDPadDownButtonPressed");
}

void onDPadLeftButtonPressed() {
  Serial.println("Console: onDPadLeftButtonPressed");
}

void onLeftJoystickChanged(int nJoyX, int nJoyY) {
  Serial.print("Console: leftJoystick - "),
    Serial.print(nJoyX), Serial.print(", "), Serial.println(nJoyY);
}

void onRightJoystickChanged(int nJoyX, int nJoyY) {
  Serial.print("Console: rightJoystick - "),
    Serial.print(nJoyX), Serial.print(", "), Serial.println(nJoyY);
}

PS2Listener ps2Controller;
PS2EventTrigger ps2Processor;

void setup() {
  Serial.begin(57600);

  ps2Processor.setOnStartButtonPressed(onStartButtonPressed);
  ps2Processor.setOnSelectButtonPressed(onSelectButtonPressed);
  ps2Processor.setOnAnalogButtonPressed(onAnalogButtonPressed);
  ps2Processor.setOnDPadUpButtonPressed(onDPadUpButtonPressed);
  ps2Processor.setOnDPadRightButtonPressed(onDPadRightButtonPressed);
  ps2Processor.setOnDPadDownButtonPressed(onDPadDownButtonPressed);
  ps2Processor.setOnDPadLeftButtonPressed(onDPadLeftButtonPressed);
  ps2Processor.setOnLeftJoystickChanged(onLeftJoystickChanged);
  ps2Processor.setOnRightJoystickChanged(onRightJoystickChanged);

  ps2Controller.set(&ps2Processor);
  ps2Controller.begin();
}

void loop() {
  uint32_t begin = millis();
  ps2Controller.loop();
  delay(max(200 + begin - millis(), 0));
}
