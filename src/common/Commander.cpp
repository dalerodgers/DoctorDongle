#include "Commander.h"

#include <string>

///////////////////////////////////////////////////////////////////////////////

Commander::Commander()
{
    clr_RequiredIf();
}

///////////////////////////////////////////////////////////////////////////////

void Commander::clr_RequiredIf()
{
    requiredIf_ = nullptr;
}

///////////////////////////////////////////////////////////////////////////////

void Commander::set_RequiredIf( RequiredIf& requiredIf )
{
    requiredIf_ = &requiredIf;
}

///////////////////////////////////////////////////////////////////////////////

void Commander::defaults()
{
    set_NAME();
    get_A2DPSTAT();
    get_HFPSTAT();
    get_MICGAIN();
    set_SPKVOL( 15, 15 );
    set_AUDROUTE__None();
    req_PLIST();
}

///////////////////////////////////////////////////////////////////////////////

void Commander::pair( const char* macAddress )
{
    if( nullptr != requiredIf_ )
    {
        const std::string temp( "AT+A2DPCONN=" + std::string( macAddress ) );
        requiredIf_->Transmit( temp.c_str() );
    }
}

///////////////////////////////////////////////////////////////////////////////)

void Commander::disconnect()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+AUDROUTE=0" );
        requiredIf_->Transmit( "AT+A2DPDISC" );
        requiredIf_->Transmit( "AT+HFPDISC" );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::reboot()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+REBOOT" );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::set_NAME()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+NAME=Doctor Dongle,0" );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::get_A2DPSTAT()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+A2DPSTAT" );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::get_HFPSTAT()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+HFPSTAT" );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::get_MICGAIN()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+MICGAIN" );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::set_MICGAIN( int a2dp, int hfp )
{
    if( nullptr != requiredIf_ )
    {
        if( a2dp > 14 )
        {
            a2dp = 14;
        }

        if( hfp > 14 )
        {
            hfp = 14;
        }

        const std::string temp( "AT+MICGAIN=" + std::to_string( a2dp ) + "," + std::to_string( hfp ) );
        requiredIf_->Transmit( temp.c_str() );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::set_SPKVOL( int a2dp, int hfp )
{
    if( nullptr != requiredIf_ )
    {
        if( a2dp > 15 )
        {
            a2dp = 15;
        }

        if( hfp > 15 )
        {
            hfp = 15;
        }

        const std::string temp( "AT+SPKVOL=" + std::to_string( a2dp ) + "," + std::to_string( hfp ) );
        requiredIf_->Transmit( temp.c_str() );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::clr_PLIST()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+PLIST=0" );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::req_PLIST()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+PLIST", false );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::set_AUDROUTE__A2DP()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+AUDROUTE=1" );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::set_AUDROUTE__HFP()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+AUDROUTE=2" );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::set_AUDROUTE__None()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+AUDROUTE=0" );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::req_SCAN()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+SCAN=1", false );
    }
}

///////////////////////////////////////////////////////////////////////////////

void Commander::get_VER()
{
    if( nullptr != requiredIf_ )
    {
        requiredIf_->Transmit( "AT+VER" );
    }
}

///////////////////////////////////////////////////////////////////////////////
