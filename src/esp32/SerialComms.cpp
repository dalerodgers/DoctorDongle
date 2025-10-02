#include "SerialComms.h"

#include "Pins.h"
#include <Arduino.h>

///////////////////////////////////////////////////////////////////////////////

SerialComms::SerialComms( Receiver& receiver ) :
    receiver_( receiver )
{
    buffer_.reserve( 100 );
}

///////////////////////////////////////////////////////////////////////////////

void SerialComms::initialise()
{
    Serial2.begin( 115200, SERIAL_8N1, Pins::SERIAL_RX, Pins::SERIAL_TX );
}

///////////////////////////////////////////////////////////////////////////////

void SerialComms::loop()
{  
    while( Serial2.available() )
    {
        const char temp = static_cast<char>( Serial2.read() );

        if( temp == '\n' )
        {
            if( !buffer_.empty() )
            {
                if( buffer_.back() == '\r' )
                {
                    buffer_.pop_back();

                    if( !buffer_.empty() )
                    {
                        Serial.printf( "RX [%s]\n", buffer_.c_str() );
                        receiver_.OnReponse( buffer_ );
                        buffer_.clear();
                    }                        
                }                
            }
        }
        else
        {
            buffer_.push_back( temp );
        }
    }
}

///////////////////////////////////////////////////////////////////////////////