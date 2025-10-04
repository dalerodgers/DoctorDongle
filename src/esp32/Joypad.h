#ifndef Joypad_H
#define Joypad_H

#include "Button2.h"

#define USE_JOYPAD

class Joypad
{
public:
    static void initialise();
    static void loop();

private:
#ifndef USE_JOYPAD
    static Button2 button_UP;
    static Button2 button_DOWN;
#else
    static Button2 button_A;
    static Button2 button_B;
    static Button2 button_C;
    static Button2 button_D;
    static Button2 button_E;
#endif
};

#endif