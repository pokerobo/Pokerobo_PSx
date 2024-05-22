#ifndef __POKEROBO_PSX_PS2_CONTROL_PROCESSOR_H__
#define __POKEROBO_PSX_PS2_CONTROL_PROCESSOR_H__

#include "PS2_Controller.h"

class PS2ControlProcessor: public PS2Processor {
  public:
    uint32_t process(PS2ControlPacket* packet);
    virtual void processStartButtonPressedEvent();
    virtual void processSelectButtonPressedEvent();
    virtual void processAnalogButtonPressedEvent();
    virtual void processDPadUpButtonPressedEvent();
    virtual void processDPadRightButtonPressedEvent();
    virtual void processDPadDownButtonPressedEvent();
    virtual void processDPadLeftButtonPressedEvent();
    virtual void processLeftJoystickChangeEvent(int nJoyX, int nJoyY);
    virtual void processRightJoystickChangeEvent(int nJoyX, int nJoyY);
  protected:
    virtual bool checkButtonPress(uint16_t pressed, uint16_t mask);
    virtual uint16_t processButtonPress(uint16_t buttons);
    virtual int processJoystickChange(int, int, char);
    virtual bool isJoystickChanged(int, int);
    virtual int adjustJoystickX(int nJoyX);
    virtual int adjustJoystickY(int nJoyY);
};

#endif
