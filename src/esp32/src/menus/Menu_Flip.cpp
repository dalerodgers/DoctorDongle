#include "Menu_Flip.h"

#include "../../Callbacks.h"
#include "../../Settings.h"

///////////////////////////////////////////////////////////////////////////////

Menu_Flip::Menu_Flip( TFT_eSPI& tft ) :
    Menu( tft )
{
    ;   // do nothing
}

///////////////////////////////////////////////////////////////////////////////

void Menu_Flip::Start()
{
    initialise();
    setTitle( "Flip screen" );
    setBack( &Callbacks::Menu_Flip__BACK );   

    if( !Settings::flipped() )
    {
        setOption( 1, "Flip", &Callbacks::Menu_Flip__Flip );
    }
    else
    {
        setOption( 1, "Do not flip", &Callbacks::Menu_Flip__DoNotFlip );
    }

    Menu::Start();
}

///////////////////////////////////////////////////////////////////////////////
