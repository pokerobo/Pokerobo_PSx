#include "PS2_ControlProcessor.h"

uint32_t PS2ControlProcessor::process(PS2ControlPacket* packet) {
  uint16_t pressed = processButtonPress(packet->getPressingFlags());
  if (pressed) {
    return pressed;
  }
  return processJoystickChange(packet->getX(), packet->getY(), 'L');
}

//-------------------------------------------------------------------------------------------------

bool PS2ControlProcessor::checkButtonPress(uint16_t pressed, uint16_t mask) {
  return pressed & mask;
}

uint16_t PS2ControlProcessor::processButtonPress(uint16_t pressed) {
  uint16_t checked = 0;

  if(checkButtonPress(pressed, MASK_START_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "START", " is pushed");
    }
    #endif
    processStartButtonPressedEvent();
    checked |= MASK_START_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_SELECT_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "SELECT", " is pushed");
    }
    #endif
    processSelectButtonPressedEvent();
    checked |= MASK_SELECT_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_ANALOG_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "ANALOG", " is pushed");
    }
    #endif
    processAnalogButtonPressedEvent();
    checked |= MASK_ANALOG_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_UP_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "PAD", "_", "UP", " is pushed");
    }
    #endif
    processDPadUpButtonPressedEvent();
    checked |= MASK_UP_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_RIGHT_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "PAD", "_", "RIGHT", " is pushed");
    }
    #endif
    processDPadRightButtonPressedEvent();
    checked |= MASK_RIGHT_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_DOWN_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "PAD", "_", "DOWN", " is pushed");
    }
    #endif
    processDPadDownButtonPressedEvent();
    checked |= MASK_DOWN_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_LEFT_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "PAD", "_", "LEFT", " is pushed");
    }
    #endif
    processDPadLeftButtonPressedEvent();
    checked |= MASK_LEFT_BUTTON;
  }

  return checked;
}

int PS2ControlProcessor::processJoystickChange(int nJoyX, int nJoyY, char label) {
  nJoyX = adjustJoystickX(nJoyX);
  nJoyY = adjustJoystickY(nJoyY);

  if (!isJoystickChanged(nJoyX, nJoyY)) {
    return 0;
  }

  #if POKEROBO_PSX_DEBUG_ENABLED
  if (isDebugEnabled()) {
    char l_[2] = { label, '\0' };
    getLogger()->debug("Input", "Controller", "::", "process", "JoystickChange", "()", " - ", l_, ": ");
    char x_[7], y_[7];
    getLogger()->debug(" - ", "X", ": ", itoa(nJoyX, x_, 10));
    getLogger()->debug(" - ", "Y", ": ", itoa(nJoyY, y_, 10));
  }
  #endif

  int flag = 0;

  if (label == 'L') {
    processLeftJoystickChangeEvent(nJoyX, nJoyY);
    flag |= 2;
  }

  if (label == 'R') {
    processRightJoystickChangeEvent(nJoyX, nJoyY);
    flag |= 1;
  }

  #if POKEROBO_PSX_DEBUG_ENABLED
  if (isDebugEnabled()) {
    char l_[2] = { label, '\0' };
    getLogger()->debug("Input", "Controller", "::", "process", "JoystickChange", "()", " - ", l_, ": ", "not registered");
  }
  #endif

  return flag;
}

//-------------------------------------------------------------------------------------------------

bool PS2ControlProcessor::isJoystickChanged(int nJoyX, int nJoyY) {
  #if defined(PS2_JOYSTICK_CHECKING_CHANGE)
  return nJoyX >= PS2_JOYSTICK_DEADZONE_X || nJoyX <= -PS2_JOYSTICK_DEADZONE_X ||
      nJoyY >= PS2_JOYSTICK_DEADZONE_Y || nJoyY <= -PS2_JOYSTICK_DEADZONE_Y;
  #else
  return true;
  #endif
}

int PS2ControlProcessor::adjustJoystickX(int nJoyX) {
  return map(nJoyX, 0, 1024, PS2_JOYSTICK_RANGE_X, -PS2_JOYSTICK_RANGE_X);
}

int PS2ControlProcessor::adjustJoystickY(int nJoyY) {
  return map(nJoyY, 0, 1024, PS2_JOYSTICK_RANGE_Y, -PS2_JOYSTICK_RANGE_Y);
}

//-------------------------------------------------------------------------------------------------

void PS2ControlProcessor::processStartButtonPressedEvent() {
}

void PS2ControlProcessor::processSelectButtonPressedEvent() {
}

void PS2ControlProcessor::processAnalogButtonPressedEvent() {
}

void PS2ControlProcessor::processDPadUpButtonPressedEvent() {
}

void PS2ControlProcessor::processDPadRightButtonPressedEvent() {
}

void PS2ControlProcessor::processDPadDownButtonPressedEvent() {
}

void PS2ControlProcessor::processDPadLeftButtonPressedEvent() {
}

void PS2ControlProcessor::processLeftJoystickChangeEvent(int nJoyX, int nJoyY) {
}

void PS2ControlProcessor::processRightJoystickChangeEvent(int nJoyX, int nJoyY) {
}
