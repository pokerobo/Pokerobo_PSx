#ifndef __POKEROBO_PSX_PS2_CONTROLLER_H__
#define __POKEROBO_PSX_PS2_CONTROLLER_H__

#include "PS2_Commons.h"
#include <PS2X_lib.h>

#ifndef __PS2INIT_LOG_ENABLED__
#define __PS2INIT_LOG_ENABLED__ (__LOADING_LOG_ENABLED__ || 0)
#endif

#define PS2_JOYSTICK_DEADZONE_X   64
#define PS2_JOYSTICK_DEADZONE_Y   64

#define PS2_JOYSTICK_RANGE_X      255
#define PS2_JOYSTICK_RANGE_Y      255

#define DEBUG_DEFAULT       true

#define GAMEPAD_ATTENTION   10
#define GAMEPAD_COMMAND     11
#define GAMEPAD_DATA        12
#define GAMEPAD_CLOCK       13

#define MASK_UP_BUTTON     1U << 0
#define MASK_RIGHT_BUTTON  1U << 1
#define MASK_DOWN_BUTTON   1U << 2
#define MASK_LEFT_BUTTON   1U << 3
#define MASK_START_BUTTON  1U << 4
#define MASK_SELECT_BUTTON 1U << 5
#define MASK_ANALOG_BUTTON 1U << 6

class PS2Controller_ {
  public:
    PS2Controller_();
    void begin();
    int loop();
    bool hasError();
    void showError();
    void reload();
    virtual int check();
  protected:
    bool isDebugEnabled();
    PSxDebugLogger* getLogger();
    PS2X ps2x;
  private:
    bool _debugEnabled;
    PSxDebugLogger* _logger = NULL;
    int _errorCode;
    bool _errorDisplayed;
};

class PS2ControlPacket {
  public:
    static const uint8_t messageSize;
    PS2ControlPacket(uint16_t buttons, uint16_t x, uint16_t y, uint32_t extras);
    PS2ControlPacket(uint16_t x=0, uint16_t y=0, uint16_t pressingFlags=0, uint16_t togglingFlags=0, uint32_t extras=0);
    void update(uint16_t buttons, uint16_t x, uint16_t y, uint32_t extras);
    void update(uint16_t x, uint16_t y, uint16_t pressingFlags, uint16_t togglingFlags, uint32_t extras);
    uint16_t getPressingFlags();
    uint16_t getTogglingFlags();
    uint16_t getX();
    uint16_t getY();
    uint32_t getExtras();
    uint8_t length();
    void* deserialize(uint8_t* buf);
  private:
    uint16_t _pressingFlags = 0;
    uint16_t _togglingFlags = 0;
    uint16_t _x = 0;
    uint16_t _y = 0;
    uint32_t _extras = 0;
};

class PS2Processor {
  public:
    virtual uint32_t process(PS2ControlPacket* packet);
    void setDebugEnabled(bool enabled);
    void setDebugLogger(PSxDebugLogger* logger);
  protected:
    bool isDebugEnabled();
    PSxDebugLogger* getLogger();
  private:
    bool _debugEnabled;
    PSxDebugLogger* _logger = NULL;
};

class PS2Listener: public PS2Controller_ {
  public:
    PS2Listener(): PS2Controller_() {};
    void set(PS2Processor* eventProcessor);
    virtual int check();
  protected:
    int read(PS2ControlPacket* packet);
  private:
    PS2Processor* _eventProcessor = NULL;
};

#endif
