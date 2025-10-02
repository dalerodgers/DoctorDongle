#include "Menu_Scanning.h"

#include "../../Callbacks.h"





#include <Arduino.h>
#include "../../Globals.h"

///////////////////////////////////////////////////////////////////////////////

Menu_Scanning::Menu_Scanning( TFT_eSPI& tft ) :
    Menu( tft )
{
    setTitle( "Scanning..." );
    setBack( &Callbacks::Menu_Scanning__BACK );
}

///////////////////////////////////////////////////////////////////////////////

void Menu_Scanning::Start()
{
    Menu::Start();

    delay(5000);

    std::vector<Device> eric;
    eric.push_back( { "Bob the dooley", "ABCDEFGH" } );
    eric.push_back( { "Sea of Tranquility", "12345678" } );
    eric.push_back( { "a", "12345678" } );
    eric.push_back( { "b", "12345678" } );
    eric.push_back( { "c", "12345678" } );
    
    Globals::callbacks.on_ScanList( eric );
}

///////////////////////////////////////////////////////////////////////////////
