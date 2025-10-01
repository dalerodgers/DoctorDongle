#include "Menu_Scanned.h"

#include "Callbacks.h"

///////////////////////////////////////////////////////////////////////////////

Menu_Scanned::Menu_Scanned( TFT_eSPI& tft ) :
    Menu( tft )
{
    // do nothing
}

///////////////////////////////////////////////////////////////////////////////

void Menu_Scanned::Start()
{
    initialise();
    setTitle( "Scanned Connections" );
    setBack( &Callbacks::Menu_Scanned_BACK );

    int32_t i = 0;
    auto iter = Callbacks::scanList.begin();

    while( ( iter != Callbacks::scanList.end() ) && ( i< Menu::MAX_OPTIONS ) )
    {
        Menu::setOption(i, iter->name.c_str(), Callbacks::Menu_Scanned_N[i] );

        iter++;
        i++;
    }

    Menu::Start();
}

///////////////////////////////////////////////////////////////////////////////