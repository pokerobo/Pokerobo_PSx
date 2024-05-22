#include "PS2_EventTrigger.h"

void PS2EventTrigger::set(PS2ControlProcessor* controlProcessor) {
  _controlProcessor = controlProcessor;
}

void PS2EventTrigger::setOnStartButtonPressed(void (*function)()) {
  _onStartButtonPressed = function;
};

void PS2EventTrigger::setOnSelectButtonPressed(void (*function)()) {
  _onSelectButtonPressed = function;
};

void PS2EventTrigger::setOnAnalogButtonPressed(void (*function)()) {
  _onAnalogButtonPressed = function;
};

void PS2EventTrigger::setOnDPadUpButtonPressed(void (*function)()) {
  _onDPadUpButtonPressed = function;
};

void PS2EventTrigger::setOnDPadRightButtonPressed(void (*function)()) {
  _onDPadRightButtonPressed = function;
};

void PS2EventTrigger::setOnDPadDownButtonPressed(void (*function)()) {
  _onDPadDownButtonPressed = function;
};

void PS2EventTrigger::setOnDPadLeftButtonPressed(void (*function)()) {
  _onDPadLeftButtonPressed = function;
};

void PS2EventTrigger::setOnLeftJoystickChanged(void (*function)(int, int)) {
  _onLeftJoystickChanged = function;
}

void PS2EventTrigger::setOnRightJoystickChanged(void (*function)(int, int)) {
  _onRightJoystickChanged = function;
};

void PS2EventTrigger::processStartButtonPressedEvent() {
  if (_onStartButtonPressed != NULL) {
    _onStartButtonPressed();
  } else if (_controlProcessor != NULL) {
    _controlProcessor->processStartButtonPressedEvent();
  }
}

void PS2EventTrigger::processSelectButtonPressedEvent() {
  if (_onSelectButtonPressed != NULL) {
    _onSelectButtonPressed();
  } else if (_controlProcessor != NULL) {
    _controlProcessor->processSelectButtonPressedEvent();
  }
}

void PS2EventTrigger::processAnalogButtonPressedEvent() {
  if (_onAnalogButtonPressed != NULL) {
    _onAnalogButtonPressed();
  } else if (_controlProcessor != NULL) {
    _controlProcessor->processAnalogButtonPressedEvent();
  }
}

void PS2EventTrigger::processDPadUpButtonPressedEvent() {
  if (_onDPadUpButtonPressed != NULL) {
    _onDPadUpButtonPressed();
  } else if (_controlProcessor != NULL) {
    _controlProcessor->processDPadUpButtonPressedEvent();
  }
}

void PS2EventTrigger::processDPadRightButtonPressedEvent() {
  if (_onDPadRightButtonPressed != NULL) {
    _onDPadRightButtonPressed();
  } else if (_controlProcessor != NULL) {
    _controlProcessor->processDPadRightButtonPressedEvent();
  }
}

void PS2EventTrigger::processDPadDownButtonPressedEvent() {
  if (_onDPadDownButtonPressed != NULL) {
    _onDPadDownButtonPressed();
  } else if (_controlProcessor != NULL) {
    _controlProcessor->processDPadDownButtonPressedEvent();
  }
}

void PS2EventTrigger::processDPadLeftButtonPressedEvent() {
  if (_onDPadLeftButtonPressed != NULL) {
    _onDPadLeftButtonPressed();
  } else if (_controlProcessor != NULL) {
    _controlProcessor->processDPadLeftButtonPressedEvent();
  }
}

void PS2EventTrigger::processLeftJoystickChangeEvent(int nJoyX, int nJoyY) {
  if (_onLeftJoystickChanged != NULL) {
    _onLeftJoystickChanged(nJoyX, nJoyY);
  } else if (_controlProcessor != NULL) {
    _controlProcessor->processLeftJoystickChangeEvent(nJoyX, nJoyY);
  }
}

void PS2EventTrigger::processRightJoystickChangeEvent(int nJoyX, int nJoyY) {
  if (_onRightJoystickChanged != NULL) {
    _onRightJoystickChanged(nJoyX, nJoyY);
  } else if (_controlProcessor != NULL) {
    _controlProcessor->processRightJoystickChangeEvent(nJoyX, nJoyY);
  }
}
