#include "Settings.h"

#include <nvs_flash.h>
#include "Globals.h"
#include "Joypad.h"

///////////////////////////////////////////////////////////////////////////////

bool Settings::flipped_ = false;
Preferences Settings::preferences_;

///////////////////////////////////////////////////////////////////////////////

void Settings::load()
{
    preferences_.begin( "DoctorDongle", true ); // ro
    //flipped_ = preferences_.getBool( "flipped", false );
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
    preferences_.begin( "DoctorDongle", false ); // rw
    preferences_.putBool( "flipped", flipped );
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