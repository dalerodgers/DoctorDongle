#include "Joypad.h"

#include "Callbacks.h"
#include "Pins.h"

///////////////////////////////////////////////////////////////////////////////

#ifndef USE_JOYPAD
Button2 Joypad::button_UP( Pins::BUTTON_1 );
Button2 Joypad::button_DOWN( Pins::BUTTON_2 );
#else
Button2 Joypad::button_A( Pins::JOY_A, INPUT_PULLUP, true );
Button2 Joypad::button_B( Pins::JOY_B, INPUT_PULLUP, true );
Button2 Joypad::button_C( Pins::JOY_C, INPUT_PULLUP, true );
Button2 Joypad::button_D( Pins::JOY_D, INPUT_PULLUP, true );
Button2 Joypad::button_E( Pins::JOY_E, INPUT_PULLUP, true );
#endif

///////////////////////////////////////////////////////////////////////////////

void Joypad::initialise()
{
#ifndef USE_JOYPAD
    button_UP.setClickHandler( &Callbacks::button_UP );
    button_UP.setDoubleClickHandler( &Callbacks::button_ENTER );
    button_UP.setTripleClickHandler( &Callbacks::button_LEFT );

    button_DOWN.setClickHandler( &Callbacks::button_DOWN );
    button_DOWN.setDoubleClickHandler( &Callbacks::button_ENTER );
    button_DOWN.setTripleClickHandler( &Callbacks::button_RIGHT );    
#else
    button_A.setTapHandler( &Callbacks::button_UP );
    button_B.setTapHandler( &Callbacks::button_LEFT );
    button_C.setTapHandler( &Callbacks::button_DOWN );
    button_D.setTapHandler( &Callbacks::button_RIGHT );
    button_E.setTapHandler( &Callbacks::button_ENTER );
#endif
}

///////////////////////////////////////////////////////////////////////////////

void Joypad::loop()
{
#ifndef USE_JOYPAD
    button_UP.loop();
    button_DOWN.loop();
#else
    button_A.loop();
    button_B.loop();
    button_C.loop();
    button_D.loop();
    button_E.loop();
#endif
}

///////////////////////////////////////////////////////////////////////////////