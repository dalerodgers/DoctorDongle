#include "Settings.h"

#include <nvs_flash.h>
#include "Globals.h"
#include "Joypad.h"

//#define WIPE_ALL

#ifdef WIPE_ALL
#include <nvs_flash.h>
#endif

///////////////////////////////////////////////////////////////////////////////

bool Settings::flipped_ = false;
Preferences Settings::preferences_;

///////////////////////////////////////////////////////////////////////////////

void Settings::load()
{
#ifdef WIPE_ALL
    nvs_flash_erase();      // erase the NVS partition and...
    nvs_flash_init();       // initialize the NVS partition.
    while (true);
#endif

    preferences_.begin( "DD", true ); // ro

    if( !preferences_.isKey( "nvmInitialised" ) )
    {
        Serial.println( "Initialising NVM" );

        preferences_.end();
        preferences_.begin( "DD", false ); // rw

        preferences_.putBool( "flipped", false );
        preferences_.putBool( "nvmInitialised", true );
        
        preferences_.end();
        preferences_.begin( "DD", true ); // ro            
    }
    
    flipped_ = preferences_.getBool( "flipped" );
    preferences_.end();

    if( !flipped_ )
    {
        flipOff();
    }
    else
    {
        flipOn();
    }
}

///////////////////////////////////////////////////////////////////////////////

void Settings::save()
{
    Serial.printf("Saving: %d\n", flipped_ );

    preferences_.begin( "DD", false ); // rw
    preferences_.putBool( "flipped", flipped_ );
    preferences_.end();

}

///////////////////////////////////////////////////////////////////////////////

void Settings::flipOff()
{
    flipped_ = false;
    Globals::tft.setRotation( 1 );
    Joypad::onFlipChange();
}

///////////////////////////////////////////////////////////////////////////////

void Settings::flipOn()
{
    flipped_ = true;
    Globals::tft.setRotation( 3 );
    Joypad::onFlipChange();
}

///////////////////////////////////////////////////////////////////////////////

bool Settings::flipped()
{
    return flipped_;
}

///////////////////////////////////////////////////////////////////////////////