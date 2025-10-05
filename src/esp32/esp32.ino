#include "Callbacks.h" 
#include "Globals.h"
#include "Module.h"
#include "Status.h"
#include "Joypad.h"
#include "Settings.h"

///////////////////////////////////////////////////////////////////////////////

void setup()
{
    Serial.begin(115200);
    Serial.println("Start");

    Status::initialise();

    Globals::tft.init();
    Settings::load();
    Globals::tft.fillScreen( TFT_BLACK );

    Joypad::initialise();

    Globals::serialComms.initialise();
    Globals::commander.set_RequiredIf( Globals::serialComms );

    Module::initialise();
}

///////////////////////////////////////////////////////////////////////////////

void loop()
{
    if( Callbacks::isOkay )
    {
        Joypad::loop();
        Callbacks::loop();
        Status::loop();
    }
    else
    {
        Module::loop();
    }

    Globals::serialComms.loop();
}

///////////////////////////////////////////////////////////////////////////////
