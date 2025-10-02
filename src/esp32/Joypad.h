#ifndef Joypad_H
#define Joypad_H

#include "Button2.h"

class Joypad
{
public:
    static void initialise();
    static void loop();

private:
    static Button2 button_UP;
    static Button2 button_DOWN;
};

#endif