#include "Globals.h"

namespace Globals
{
    TFT_eSPI tft( 135, 240 );
    
    Menu_Main menu_Main( tft );
    Menu_Scanning menu_Scanning( tft );
    Menu_PreviousConnections menu_PreviousConnections( tft );
    Menu_Scanned menu_Scanned( tft );
    Menu_Delete menu_Delete( tft );
}