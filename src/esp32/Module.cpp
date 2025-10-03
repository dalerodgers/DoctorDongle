#include "Module.h"

#include "Callbacks.h"
#include "Globals.h"

///////////////////////////////////////////////////////////////////////////////

unsigned long Module::flashTimer_;
uint32_t Module::flashColour_;

///////////////////////////////////////////////////////////////////////////////

void Module::initialise()
{
    flashTimer_ = millis() - 500U;
    flashColour_ = TFT_RED;
}

///////////////////////////////////////////////////////////////////////////////

void Module::loop()
{
    if( ( millis() - flashTimer_ ) > 500U )
    {
        flashTimer_ = millis();

        if( TFT_RED == flashColour_ )
        {
            flashColour_ = TFT_BLACK;
            Globals::commander.get_VER();
        }
        else
        {
            flashColour_ = TFT_RED;
        }

        Globals::tft.fillRoundRect( 35, 35, Globals::tft.width() - 70, Globals::tft.height() - 70, 35, flashColour_ );
    }
}

///////////////////////////////////////////////////////////////////////////////