#include "PS2_Controller.h"

PS2Controller_::PS2Controller_() {
  _debugEnabled = true;
  _errorCode = 0;
  _errorDisplayed = false;
}

void PS2Controller_::begin() {
  //
  // setup pins and settings: 
  // GamePad(clock, command, attention, data, Pressures?, Rumble?) check for error
  _errorCode = ps2x.config_gamepad(GAMEPAD_CLOCK, GAMEPAD_COMMAND, GAMEPAD_ATTENTION, GAMEPAD_DATA, false, false);

  // Check for error
  if(_errorCode == 0) {
    #if __PS2INIT_LOG_ENABLED__
    debugLog("Controller", " ", "found, configured successful");
    #endif
  }
  else if(_errorCode == 1) {
    #if __PS2INIT_LOG_ENABLED__
    debugLog("Controller", " ", "not found, check wiring or reset the Arduino");
    #endif
  }
  else if(_errorCode == 2) {
    #if __PS2INIT_LOG_ENABLED__
    debugLog("Controller", " ", "found but not accepting commands");
    #endif
  }
  else if(_errorCode == 3) {
    #if __PS2INIT_LOG_ENABLED__
    debugLog("Controller", " ", "refusing to enter Pressures mode."); // may not support it
    #endif
  }
  //
  // Check for the type of controller
  byte ps2Type = ps2x.readType();
  switch(ps2Type) {
    case 0:
      #if __PS2INIT_LOG_ENABLED__
      debugLog("Unknown", " ", "Controller", " ", "type");
      #endif
      break;
    case 1:
      #if __PS2INIT_LOG_ENABLED__
      debugLog("DualShock", " ", "Controller", " ", "Found");
      #endif
      break;
    case 2:
      #if __PS2INIT_LOG_ENABLED__
      debugLog("GuitarHero", " ", "Controller", " ", "Found");
      #endif
      break;
    default:
      #if __PS2INIT_LOG_ENABLED__
      char b_[5];
      debugLog("Invalid", " ", "Controller", " ", "type", ": ", itoa(ps2Type, b_, 10));
      #endif
      NULL;
  }
};

bool PS2Controller_::hasError() {
  return _errorCode != 0;
};

void PS2Controller_::showError() {
  if (!_errorDisplayed) {
    debugLog("Error, terminated!");
    _errorDisplayed = true;
  }
};

void PS2Controller_::reload() {
  begin();
};

int PS2Controller_::loop() {
  if(hasError()) { //skip loop if no controller found
    showError();
    debugLog("Reload ...");
    delay(1000);
    reload();
    return 0;
  } else { //DualShock Controller
    return check();
  }
}

bool PS2Controller_::isDebugEnabled() {
  return _debugEnabled;
}

//-------------------------------------------------------------------------------------------------

#if __JOYSTICK_MESSAGE_STRUCTURE__ == CONTROL_PACKET_V1
const uint8_t PS2ControlPacket::messageSize = 0 // SIGNATURE
    + sizeof(uint16_t) // pressingFlags
    + sizeof(uint16_t) // Joystick-X
    + sizeof(uint16_t) // Joystick-Y
    + sizeof(uint32_t);
#else
const uint8_t PS2ControlPacket::messageSize = 0 // SIGNATURE
    + sizeof(uint16_t) // pressingFlags
    + sizeof(uint16_t) // togglingFlags
    + sizeof(uint16_t) // Joystick-X
    + sizeof(uint16_t) // Joystick-Y
    + sizeof(uint32_t);
#endif

PS2ControlPacket::PS2ControlPacket(uint16_t buttons, uint16_t x, uint16_t y, uint32_t extras) {
  update(buttons, x, y, extras);
}

void PS2ControlPacket::update(uint16_t buttons, uint16_t x, uint16_t y, uint32_t extras) {
  _pressingFlags = buttons;
  _x = x;
  _y = y;
  _extras = extras;
}

PS2ControlPacket::PS2ControlPacket(uint16_t x, uint16_t y, uint16_t pressingFlags, uint16_t togglingFlags, uint32_t extras) {
  update(x, y, pressingFlags, togglingFlags, extras);
}

void PS2ControlPacket::update(uint16_t x, uint16_t y, uint16_t pressingFlags, uint16_t togglingFlags, uint32_t extras) {
  _x = x;
  _y = y;
  _pressingFlags = pressingFlags;
  _togglingFlags = togglingFlags;
  _extras = extras;
}

uint16_t PS2ControlPacket::getPressingFlags() {
  return _pressingFlags;
}

uint16_t PS2ControlPacket::getTogglingFlags() {
  return _togglingFlags;
}

uint16_t PS2ControlPacket::getX() {
  return _x;
}

uint16_t PS2ControlPacket::getY() {
  return _y;
}

uint32_t PS2ControlPacket::getExtras() {
  return _extras;
}

uint8_t PS2ControlPacket::length() {
  return messageSize;
}

bool decodeMessage(uint8_t* msg, char* cmd, uint16_t* buttons, uint16_t* x, uint16_t* y, uint32_t* extras);
bool decodeMessage(uint8_t* msg, char* cmd,
    uint16_t* x, uint16_t* y,
    uint16_t* pressingFlags,
    uint16_t* togglingFlags,
    uint32_t* extras);

void* PS2ControlPacket::deserialize(uint8_t* buf) {
  if (buf == NULL) {
    return NULL;
  }
  #if __JOYSTICK_MESSAGE_STRUCTURE__ == CONTROL_PACKET_V1
  decodeMessage(buf, NULL, &(_pressingFlags), &(_x), &(_y), &(_extras));
  #else
  decodeMessage(buf, NULL, &(_x), &(_y), &(_pressingFlags), &(_togglingFlags), &(_extras));
  #endif

  return this;
}

void PS2Listener::set(PS2Processor* eventProcessor) {
  _eventProcessor = eventProcessor;
};

int PS2Listener::read(PS2ControlPacket* action) {
  byte vibrate = 0;
  ps2x.read_gamepad(false, vibrate); // disable vibration of the controller

  uint16_t buttons = 0;

  if(ps2x.Button(PSB_START)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "START", " is pushed");
    }
    #endif
    buttons |= MASK_START_BUTTON;
  }

  if(ps2x.Button(PSB_SELECT)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "SELECT", " is pushed");
    }
    #endif
    buttons |= MASK_SELECT_BUTTON;
  }

  if(ps2x.Button(PSB_PAD_UP)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "PAD", "_", "UP", " is pushed");
    }
    #endif
    buttons |= MASK_UP_BUTTON;
  }

  if(ps2x.Button(PSB_PAD_RIGHT)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "PAD", "_", "RIGHT", " is pushed");
    }
    #endif
    buttons |= MASK_RIGHT_BUTTON;
  }

  if(ps2x.Button(PSB_PAD_DOWN)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "PAD", "_", "DOWN", " is pushed");
    }
    #endif
    buttons |= MASK_DOWN_BUTTON;
  }

  if(ps2x.Button(PSB_PAD_LEFT)) {
    #if __RUNNING_LOG_ENABLED__
    if (isDebugEnabled()) {
      debugLog("PSB", "_", "PAD", "_", "LEFT", " is pushed");
    }
    #endif
    buttons |= MASK_LEFT_BUTTON;
  }

  int nJoyX = ps2x.Analog(PSS_LX); // read x-joystick
  int nJoyY = ps2x.Analog(PSS_LY); // read y-joystick

  uint16_t lJoyX = map(nJoyX, 0, 255, 0, 1024);
  uint16_t lJoyY = map(nJoyY, 0, 255, 0, 1024);

  action->update(buttons, lJoyX, lJoyY, 0);

  return 1;
}

int PS2Listener::check() {
  PS2ControlPacket action;

  int ok = read(&action);

  if (ok == 1) {
    if (_eventProcessor != NULL) {
      _eventProcessor->process(&action);
      return 0xff;
    }
  }

  return ok;
}

uint32_t PS2EventDispatcher::process(PS2ControlPacket* packet) {
  uint16_t pressed = processButtonPress(packet->getPressingFlags());
  if (pressed) {
    return pressed;
  }
  return processJoystickChange(packet->getX(), packet->getY(), 'L');
}

bool PS2EventDispatcher::isDebugEnabled() {
  return _debugEnabled;
}

bool PS2EventDispatcher::isJoystickChanged(int nJoyX, int nJoyY) {
  #if defined(PS2_JOYSTICK_CHECKING_CHANGE)
  return nJoyX >= PS2_JOYSTICK_DEADZONE_X || nJoyX <= -PS2_JOYSTICK_DEADZONE_X ||
      nJoyY >= PS2_JOYSTICK_DEADZONE_Y || nJoyY <= -PS2_JOYSTICK_DEADZONE_Y;
  #else
  return true;
  #endif
}

int PS2EventDispatcher::adjustJoystickX(int nJoyX) {
  return map(nJoyX, 0, 1024, PS2_JOYSTICK_RANGE_X, -PS2_JOYSTICK_RANGE_X);
}

int PS2EventDispatcher::adjustJoystickY(int nJoyY) {
  return map(nJoyY, 0, 1024, PS2_JOYSTICK_RANGE_Y, -PS2_JOYSTICK_RANGE_Y);
}
