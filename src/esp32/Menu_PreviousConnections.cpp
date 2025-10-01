#include "Menu_PreviousConnections.h"

#include "Callbacks.h"

///////////////////////////////////////////////////////////////////////////////

Menu_PreviousConnections::Menu_PreviousConnections( TFT_eSPI& tft ) :
    Menu( tft )
{
    // do nothing
}

///////////////////////////////////////////////////////////////////////////////

void Menu_PreviousConnections::Start()
{
    initialise();
    setTitle( "Previous Connections" );
    setBack( &Callbacks::Menu_PreviousConnections_BACK );

    int32_t i = 0;
    auto iter = Callbacks::pairedList.begin();

    while( ( iter != Callbacks::pairedList.end() ) && ( i< Menu::MAX_OPTIONS ) )
    {
        Menu::setOption(i, iter->name.c_str(), Callbacks::Menu_PreviousConnections_N[i] );

        iter++;
        i++;
    }

    Menu::Start();
}

///////////////////////////////////////////////////////////////////////////////