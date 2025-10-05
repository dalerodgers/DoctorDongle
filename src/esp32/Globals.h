#ifndef Globals_H
#define Globals_H

#include "TFT_eSPI.h"
#include "src/common/Commander.h"
#include "src/menus/Menu_Main.h"
#include "src/menus/Menu_Scanning.h"
#include "src/menus/Menu_PreviousConnections.h"
#include "src/menus/Menu_Scanned.h"
#include "src/menus/Menu_Delete.h"
#include "src/menus/Menu_Flip.h"
#include "SerialComms.h"

namespace Globals
{
    extern TFT_eSPI tft;
    
    extern Menu_Main menu_Main;
    extern Menu_Scanning menu_Scanning;
    extern Menu_PreviousConnections menu_PreviousConnections;
    extern Menu_Scanned menu_Scanned;
    extern Menu_Delete menu_Delete;
    extern Menu_Flip menu_Flip;

    extern Receiver receiver;
    extern SerialComms serialComms;
    extern Commander commander;
}

#endif