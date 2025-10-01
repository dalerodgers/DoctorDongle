#include "Menu_Scanning.h"

#include "Callbacks.h"





#include <Arduino.h>
#include "Globals.h"

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
    Callbacks::set_Menu( Globals::menu_Scanned );
}

///////////////////////////////////////////////////////////////////////////////