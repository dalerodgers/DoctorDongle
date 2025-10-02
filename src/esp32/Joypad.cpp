#include "Joypad.h"

#include "Callbacks.h"
#include "Pins.h"

///////////////////////////////////////////////////////////////////////////////

Button2 Joypad::button_UP( Pins::BUTTON_1 );
Button2 Joypad::button_DOWN( Pins::BUTTON_2 );

///////////////////////////////////////////////////////////////////////////////

void Joypad::initialise()
{
    button_UP.setClickHandler( &Callbacks::button_UP );
    button_UP.setDoubleClickHandler( &Callbacks::button_ENTER );
    button_UP.setTripleClickHandler( &Callbacks::button_LEFT );

    button_DOWN.setClickHandler( &Callbacks::button_DOWN );
    button_DOWN.setDoubleClickHandler( &Callbacks::button_ENTER );
    button_DOWN.setTripleClickHandler( &Callbacks::button_RIGHT );    
}

///////////////////////////////////////////////////////////////////////////////

void Joypad::loop()
{
    button_UP.loop();
    button_DOWN.loop();
}

///////////////////////////////////////////////////////////////////////////////