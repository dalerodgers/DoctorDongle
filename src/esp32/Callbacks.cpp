#include "Callbacks.h"

#include "Globals.h"
#include "Status.h"

#include "images/Note.h"
#include "images/Headset.h"

///////////////////////////////////////////////////////////////////////////

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

int Callbacks::micGain_A2DP = -1;
int Callbacks::micGain_HFP = -1;
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
    
    Globals::tft.pushImage( 0, 0, Note_WIDTH, Note_HEIGHT, Note );    
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
    else
    {
        micGain_A2DP++;

        if( micGain_A2DP > 15 )
        {
            micGain_A2DP = 15;
        }
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
    else
    {
        micGain_A2DP--;

        if( micGain_A2DP < 0 )
        {
            micGain_A2DP = 0;
        }
    }
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::button_LEFT( Button2& btn )
{
    static_cast<void>( btn );
    //lastButtonPress_ = millis();

    //if( nullptr != menu_ )
    //{
    //    menu_->down();
    //}

    if( nullptr == menu_ )
    {    
        Globals::tft.pushImage( 0, 0, Note_WIDTH, Note_HEIGHT, Note );    
        Status::refresh();

        Globals::tft.fillTriangle( 225, 55, 225, 65, 235, 60, TFT_WHITE );
        paintVolume( 219, 10 );
    }
    else
    {
        lastButtonPress_ = millis();
        menu_->back();
    }    
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::button_RIGHT( Button2& btn )
{
    static_cast<void>( btn );
    //lastButtonPress_ = millis();

    //if( nullptr != menu_ )
    //{
    //    menu_->down();
    //}

    if( nullptr == menu_ )
    {
        Globals::tft.pushImage( 0, 0, Headset_WIDTH, Headset_HEIGHT, Headset );    
        Status::refresh();

        Globals::tft.fillTriangle( 5, 60, 15, 55, 15, 65, TFT_WHITE );
        paintVolume( 5, 10 );  
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
    micGain_A2DP = val;
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

void Callbacks::paintVolume( const int32_t x, const int32_t y )
{
    Globals::tft.fillRect( x, y, 5, 15, TFT_WHITE );
    Globals::tft.fillTriangle( x+1, y+7, x+10, y, x+10, y+15, TFT_WHITE );
    Globals::tft.fillTriangle( x+16, y, x+13, y+7, x+19, y+7, TFT_WHITE );
    Globals::tft.fillTriangle( x+16, y+15, x+13, y+9, x+19, y+9, TFT_WHITE );
}

///////////////////////////////////////////////////////////////////////////