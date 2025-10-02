#ifndef Globals_H
#define Globals_H

#include "TFT_eSPI.h"
#include "Menu_Main.h"
#include "Menu_Scanning.h"
#include "Menu_PreviousConnections.h"
#include "Menu_Scanned.h"
#include "Menu_Delete.h"

namespace Globals
{
    extern TFT_eSPI tft;
    
    extern Menu_Main menu_Main;
    extern Menu_Scanning menu_Scanning;
    extern Menu_PreviousConnections menu_PreviousConnections;
    extern Menu_Scanned menu_Scanned;
    extern Menu_Delete menu_Delete;
}

#endif