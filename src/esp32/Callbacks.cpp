#include "Callbacks.h"

#include "Globals.h"
#include "Status.h"

///////////////////////////////////////////////////////////////////////////

bool Callbacks::dummyPin = false;





Menu* Callbacks::menu_ = nullptr;
unsigned long Callbacks::lastButtonPress_;

std::vector<Device> Callbacks::pairedList;
std::vector<Device> Callbacks::scanList;

const Menu::FuncPtr Callbacks::Menu_PreviousConnections_N[Menu::MAX_OPTIONS] =
{
    &Callbacks::Menu_PreviousConnections_0,
    &Callbacks::Menu_PreviousConnections_1,
    &Callbacks::Menu_PreviousConnections_2,
    &Callbacks::Menu_PreviousConnections_3
};

const Menu::FuncPtr Callbacks::Menu_Scanned_N[Menu::MAX_OPTIONS] =
{
    &Callbacks::Menu_Scanned_0,
    &Callbacks::Menu_Scanned_1,
    &Callbacks::Menu_Scanned_2,
    &Callbacks::Menu_Scanned_3
};

bool Callbacks::isConnected_A2DP = false;
bool Callbacks::isConnected_HFP = false;
std::string Callbacks::deviceName;

///////////////////////////////////////////////////////////////////////////

void Callbacks::loop()
{
    if( nullptr == menu_ )
    {
        ;   // do nothing
    }
    else if( (millis() - lastButtonPress_ ) < 60000 )
    {
        ;   // do nothing
    }
    else
    {
        clr_Menu();
    }

    static unsigned long jeff = millis(); 

    if( ( millis() - jeff ) > 500 )
    {
        jeff = millis();
        dummyPin = ( dummyPin ? false : true );      
    }
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::set_Menu( Menu &menu )
{
    menu_ = &menu;
    menu_->Start();
    Status::refresh();
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::clr_Menu()
{
    menu_ = nullptr;
    Globals::tft.fillScreen( TFT_DARKGREY );
    Status::refresh();
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::button_UP( Button2& btn )
{
    static_cast<void>( btn );
    lastButtonPress_ = millis();

    if( nullptr != menu_ )
    {
        menu_->up();
    }    
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::button_DOWN( Button2& btn )
{
    static_cast<void>( btn );
    lastButtonPress_ = millis();

    if( nullptr != menu_ )
    {
        menu_->down();
    }
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::button_ENTER( Button2& btn )
{
    static_cast<void>( btn );
    lastButtonPress_ = millis();

    if( nullptr != menu_ )
    {
        menu_->enter();
    }
    else
    {
        set_Menu( Globals::menu_Main );
    }
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Main__PreviousConnections()
{
    set_Menu( Globals::menu_PreviousConnections );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Main__ScanForNew()
{
    set_Menu( Globals::menu_Scanning );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Main__DeleteAll()
{
    set_Menu( Globals::menu_Delete );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Main__BACK()
{
    clr_Menu();
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Scanning__BACK()
{
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_PreviousConnections_0()
{
    Globals::callbacks.on_A2DP_Device( pairedList.at(0).name() );
}

///////////////////////////////////////////////////////////////////////////
 
void Callbacks::Menu_PreviousConnections_1()
{
    Globals::callbacks.on_A2DP_Device( pairedList.at(1).name() );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_PreviousConnections_2()
{
    Globals::callbacks.on_A2DP_Device( pairedList.at(2).name() );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_PreviousConnections_3()
{
    Globals::callbacks.on_A2DP_Device( pairedList.at(3).name() );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_PreviousConnections_BACK()
{
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Scanned_0()
{
}

///////////////////////////////////////////////////////////////////////////
 
void Callbacks::Menu_Scanned_1()
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Scanned_2()
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Scanned_3()
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Scanned_BACK()
{
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Delete__Delete()
{
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Delete__BACK()
{
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_OK()
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_ERR()
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_A2DP_Connected( const bool isConnected )
{
    isConnected_A2DP = isConnected;
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_A2DP_Device( const std::string& name )
{
    deviceName = name;
    Status::refresh();    
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_A2DP_MicGain( const int val )
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_AUDROUTE( const std::string& val )
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_HFP_Connected( const bool isConnected )
{
    isConnected_HFP = isConnected;
    Status::refresh();
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_HFP_Device( const std::string& name )
{
    deviceName = name;
    Status::refresh();
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_HFP_MicGain( const int val )
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_PairedList( const std::vector<Device>& deviceList )
{
    pairedList = deviceList;
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_ScanList( const std::vector<Device>& deviceList )
{
    if( &Globals::menu_Scanning == menu_ )
    {  
        scanList = deviceList;
        set_Menu( Globals::menu_Scanned );
    }
}

///////////////////////////////////////////////////////////////////////////

namespace Globals
{
    Callbacks callbacks;
}

///////////////////////////////////////////////////////////////////////////