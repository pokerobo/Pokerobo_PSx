#include "PS2_EventDispatcher.h"

//-------------------------------------------------------------------------------------------------

void PS2EventDispatcher::set(PS2ControlProcessor* controlProcessor) {
  _controlProcessor = controlProcessor;
}

void PS2EventDispatcher::setOnStartButtonPressed(void (*function)()) {
  _onStartButtonPressed = function;
};

void PS2EventDispatcher::setOnSelectButtonPressed(void (*function)()) {
  _onSelectButtonPressed = function;
};

void PS2EventDispatcher::setOnAnalogButtonPressed(void (*function)()) {
  _onAnalogButtonPressed = function;
};

void PS2EventDispatcher::setOnDPadUpButtonPressed(void (*function)()) {
  _onDPadUpButtonPressed = function;
};

void PS2EventDispatcher::setOnDPadRightButtonPressed(void (*function)()) {
  _onDPadRightButtonPressed = function;
};

void PS2EventDispatcher::setOnDPadDownButtonPressed(void (*function)()) {
  _onDPadDownButtonPressed = function;
};

void PS2EventDispatcher::setOnDPadLeftButtonPressed(void (*function)()) {
  _onDPadLeftButtonPressed = function;
};

void PS2EventDispatcher::setOnLeftJoystickChanged(void (*function)(int, int)) {
  _onLeftJoystickChanged = function;
}

void PS2EventDispatcher::setOnRightJoystickChanged(void (*function)(int, int)) {
  _onRightJoystickChanged = function;
};

//-------------------------------------------------------------------------------------------------

uint16_t PS2EventDispatcher::processButtonPress(uint16_t pressed) {
  uint16_t checked = 0;

  if(checkButtonPress(pressed, MASK_START_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "START", " is pushed");
    }
    #endif
    if (_onStartButtonPressed != NULL) {
      _onStartButtonPressed();
    } else if (_controlProcessor != NULL) {
      _controlProcessor->processStartButtonPressedEvent();
    } else {
      processStartButtonPressedEvent();
    }
    checked |= MASK_START_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_SELECT_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "SELECT", " is pushed");
    }
    #endif
    if (_onSelectButtonPressed != NULL) {
      _onSelectButtonPressed();
    } else if (_controlProcessor != NULL) {
      _controlProcessor->processSelectButtonPressedEvent();
    } else {
      processSelectButtonPressedEvent();
    }
    checked |= MASK_SELECT_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_ANALOG_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "ANALOG", " is pushed");
    }
    #endif
    if (_onAnalogButtonPressed != NULL) {
      _onAnalogButtonPressed();
    } else if (_controlProcessor != NULL) {
      _controlProcessor->processAnalogButtonPressedEvent();
    } else {
      processAnalogButtonPressedEvent();
    }
    checked |= MASK_ANALOG_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_UP_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "PAD", "_", "UP", " is pushed");
    }
    #endif
    if (_onDPadUpButtonPressed != NULL) {
      _onDPadUpButtonPressed();
    } else if (_controlProcessor != NULL) {
      _controlProcessor->processDPadUpButtonPressedEvent();
    } else {
      processDPadUpButtonPressedEvent();
    }
    checked |= MASK_UP_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_RIGHT_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "PAD", "_", "RIGHT", " is pushed");
    }
    #endif
    if (_onDPadRightButtonPressed != NULL) {
      _onDPadRightButtonPressed();
    } else if (_controlProcessor != NULL) {
      _controlProcessor->processDPadRightButtonPressedEvent();
    } else {
      processDPadRightButtonPressedEvent();
    }
    checked |= MASK_RIGHT_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_DOWN_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "PAD", "_", "DOWN", " is pushed");
    }
    #endif
    if (_onDPadDownButtonPressed != NULL) {
      _onDPadDownButtonPressed();
    } else if (_controlProcessor != NULL) {
      _controlProcessor->processDPadDownButtonPressedEvent();
    } else {
      processDPadDownButtonPressedEvent();
    }
    checked |= MASK_DOWN_BUTTON;
  }

  if(checkButtonPress(pressed, MASK_LEFT_BUTTON)) {
    #if POKEROBO_PSX_DEBUG_ENABLED
    if (isDebugEnabled()) {
      getLogger()->debug("JOY", "_", "PAD", "_", "LEFT", " is pushed");
    }
    #endif
    if (_onDPadLeftButtonPressed != NULL) {
      _onDPadLeftButtonPressed();
    } else if (_controlProcessor != NULL) {
      _controlProcessor->processDPadLeftButtonPressedEvent();
    } else {
      processDPadLeftButtonPressedEvent();
    }
    checked |= MASK_LEFT_BUTTON;
  }

  return checked;
}

int PS2EventDispatcher::processJoystickChange(int nJoyX, int nJoyY, char label) {
  nJoyX = adjustJoystickX(nJoyX);
  nJoyY = adjustJoystickY(nJoyY);

  if (!isJoystickChanged(nJoyX, nJoyY)) {
    return 0;
  }

  #if POKEROBO_PSX_DEBUG_ENABLED
  if (isDebugEnabled()) {
    char l_[2] = { 'L', '\0' };
    getLogger()->debug("Event", "Trigger", "::", "process", "JoystickChange", "()", " - ", l_, ": ");
    char x_[7], y_[7];
    getLogger()->debug(" - ", "X", ": ", itoa(nJoyX, x_, 10));
    getLogger()->debug(" - ", "Y", ": ", itoa(nJoyY, y_, 10));
  }
  #endif

  int flag = 0;

  if (label == 'L') {
    if (_onLeftJoystickChanged) {
      _onLeftJoystickChanged(nJoyX, nJoyY);
    } else if (_controlProcessor != NULL) {
      _controlProcessor->processLeftJoystickChangeEvent(nJoyX, nJoyY);
    } else {
      processLeftJoystickChangeEvent(nJoyX, nJoyY);
    }
    flag |= 0b11;
  }

  if (label == 'R') {
    if (_onRightJoystickChanged) {
      _onRightJoystickChanged(nJoyX, nJoyY);
    } else if (_controlProcessor != NULL) {
      _controlProcessor->processRightJoystickChangeEvent(nJoyX, nJoyY);
    } else {
      processRightJoystickChangeEvent(nJoyX, nJoyY);
    }
    flag |= 0b01;
  }

  #if POKEROBO_PSX_DEBUG_ENABLED
  if (isDebugEnabled()) {
    char l_[2] = { 'L', '\0' };
    getLogger()->debug("Event", "Trigger", "::", "process", "JoystickChange", "()", " - ", l_, ": ", "not registered");
  }
  #endif

  return -1;
}
