#include "SerialComms.h"

#include "Pins.h"
#include <Arduino.h>

#define SERIAL_DEBUG

///////////////////////////////////////////////////////////////////////////////

SerialComms::SerialComms( Receiver& receiver ) :
    receiver_( receiver )
{
    buffer_.reserve( 100 );
    waitingForOkay_ = false;
}

///////////////////////////////////////////////////////////////////////////////

void SerialComms::initialise()
{
    Serial2.begin( 115200, SERIAL_8N1, Pins::SERIAL_RX, Pins::SERIAL_TX );
}

///////////////////////////////////////////////////////////////////////////////

void SerialComms::loop()
{  
    // ........................................................................

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
#ifdef SERIAL_DEBUG
                        Serial.printf( "RX [%s]\n\n", buffer_.c_str() );
#endif
                        if( !waitingForOkay_ )
                        {
                            ;   // do nothing
                        }
                        else if( "OK" != buffer_ )
                        {
                            ;   // do nothing
                        }
                        else
                        {
                            waitingForOkay_ = false;
                            checkList();
                        }

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

    // ........................................................................

    if( waitingForOkay_ )
    {
        if( ( millis() - waitingForOkayTimeStart_ ) > 500 )
        {
            waitingForOkay_ = false;
            checkList();
        }
    }
}

///////////////////////////////////////////////////////////////////////////////

void SerialComms::Transmit( const char* c_str, const bool waitForOkay )
{
    waiters_.push_back( Waiter( { c_str, waitForOkay } ) );
    checkList();
}

///////////////////////////////////////////////////////////////////////////////

void SerialComms::checkList()
{
    while( !waitingForOkay_ && !waiters_.empty() )
    {
        const char* const c_str = waiters_.begin()->str.c_str();

#ifdef SERIAL_DEBUG
        Serial.printf( "TX [%s]\n", c_str );
#endif

        Serial2.print( c_str );
        Serial2.print( '\r' );
        Serial2.print( '\n' );

        if( waiters_.begin()->waitForOkay )
        {
            waitingForOkay_ = true;
            waitingForOkayTimeStart_ = millis();
        }

        waiters_.pop_front();
    }
}

///////////////////////////////////////////////////////////////////////////////