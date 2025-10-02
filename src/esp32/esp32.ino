#include "Callbacks.h" 
#include "Globals.h"
#include "Status.h"
#include "Joypad.h"

///////////////////////////////////////////////////////////////////////////////

void setup()
{
    Serial.begin(115200);
    Serial.println("Start");

    Status::initialise();

    Globals::tft.init();
    Globals::tft.setRotation(1);

    Joypad::initialise();

    std::vector<Device> eric;
    eric.push_back( { "Sea of Tranquility", "12345678" } );
    eric.push_back( { "Bob the dooley", "ABCDEFGH" } );
    Globals::callbacks.on_PairedList( eric );

    Globals::callbacks.on_A2DP_MicGain( 0 );

    Globals::serialComms.initialise();

    Callbacks::clr_Menu();
}

///////////////////////////////////////////////////////////////////////////////

void loop()
{
    Joypad::loop();
    Callbacks::loop();
    Status::loop();
    Globals::serialComms.loop();
}

///////////////////////////////////////////////////////////////////////////////
