#include "Status.h"

#include <esp_adc_cal.h>
#include "Callbacks.h"
#include "Globals.h"
#include "Pins.h"

///////////////////////////////////////////////////////////////////////////////

bool Status::lastLedState_;
unsigned long Status::lastBatteryTime_;
int Status::vref_ = 1100;

///////////////////////////////////////////////////////////////////////////////

void Status::initialise()
{
    lastLedState_ = Callbacks::dummyPin;
    lastBatteryTime_ = millis();

    esp_adc_cal_characteristics_t adc_chars;
    const esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);    //Check type of calibration value used to characterize ADC
    
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF)
    {
        Serial.printf("eFuse Vref:%u mV", adc_chars.vref);
        vref_ = adc_chars.vref;
    }
    else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP)
    {
        Serial.printf("Two Point --> coeff_a:%umV coeff_b:%umV\n", adc_chars.coeff_a, adc_chars.coeff_b);
    }
    else
    {
        Serial.println("Default Vref: 1100mV");
    }

    pinMode( Pins::ADC_EN, OUTPUT );
    digitalWrite( Pins::ADC_EN, HIGH );
}

///////////////////////////////////////////////////////////////////////////////

void Status::loop()
{
    const bool ledState = Callbacks::dummyPin;

    if( ledState != lastLedState_ )
    {
        lastLedState_ = ledState;
        paint_LED( ledState );
    }

    if( ( millis() - lastBatteryTime_ ) > 2000 )
    {
        lastBatteryTime_ = millis();
        paint_ADC();      
    }
}

///////////////////////////////////////////////////////////////////////////////

void Status::refresh()
{
    Globals::tft.fillRect( 0, Globals::tft.height() - 18, Globals::tft.width(), 18, TFT_BLACK );
    Globals::tft.fillRect( 0, Globals::tft.height() - 20, Globals::tft.width(), 2, TFT_LIGHTGREY );

    paint_LED( true );
    paint_LED( lastLedState_ );
    paint_Device();
    paint_ADC();
}

///////////////////////////////////////////////////////////////////////////////

void Status::paint_LED( const bool led )
{
    if( led )
    {
        Globals::tft.fillCircle( 6, Globals::tft.height() - 10, 6, TFT_BLUE );
    }
    else
    {
        Globals::tft.fillCircle( 6, Globals::tft.height() - 10, 4, TFT_BLACK );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Status::paint_Device()
{
    Globals::tft.setTextFont( 2 );
    Globals::tft.setTextColor( TFT_DARKGREY );
    
    if( !Callbacks::deviceName.empty() )
    {
        Globals::tft.drawString( Callbacks::deviceName.c_str(), 18, Globals::tft.height() - Globals::tft.fontHeight() - 1);
    }       
    else 
    {
        Globals::tft.drawString( "No Device", 18, Globals::tft.height() - Globals::tft.fontHeight() - 1);
    }    
}

///////////////////////////////////////////////////////////////////////////////

void Status::paint_ADC()
{
    const uint16_t v = analogRead( Pins::ADC_PIN );
    const float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref_ / 1000.0);
    
    char temp[20];
    sprintf( temp, "%1.2fV", battery_voltage );

    Globals::tft.fillRect( 200, Globals::tft.height() - 16, Globals::tft.width() - 200, 16, TFT_BLACK );        

    Globals::tft.setTextFont( 2 );

    if( battery_voltage > 4.0f )
    {
        Globals::tft.setTextColor( TFT_DARKGREY );
    }    
    else if( battery_voltage > 3.6f )
    {
        Globals::tft.setTextColor( TFT_DARKGREEN );      
    }
    else if( battery_voltage > 3.4f )
    {
        Globals::tft.setTextColor( TFT_YELLOW );
    }
    else
    {
        Globals::tft.setTextColor( TFT_RED );
    }

    Globals::tft.drawString( temp, 203, Globals::tft.height() - Globals::tft.fontHeight() - 1 );
}

///////////////////////////////////////////////////////////////////////////////