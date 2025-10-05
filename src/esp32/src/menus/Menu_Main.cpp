#include "Menu_Main.h"

#include "../../Callbacks.h"

///////////////////////////////////////////////////////////////////////////////

Menu_Main::Menu_Main( TFT_eSPI& tft ) :
    Menu( tft )
{
    setTitle( "Main" );

    setOption( 0, "Previous connections", &Callbacks::Menu_Main__PreviousConnections );
    setOption( 1, "Scan for new", &Callbacks::Menu_Main__ScanForNew );
    setOption( 2, "Delete all connections", &Callbacks::Menu_Main__DeleteAll );
    setOption( 3, "Flip screen", &Callbacks::Menu_Main__Flip );

    setBack( &Callbacks::Menu_Main__BACK );
}

///////////////////////////////////////////////////////////////////////////////

void Menu_Main::Start()
{
    Menu::Start();
}

///////////////////////////////////////////////////////////////////////////////
