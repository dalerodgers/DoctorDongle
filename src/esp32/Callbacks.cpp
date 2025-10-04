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
int Callbacks::audMode = -1;
std::string Callbacks::deviceName_A2DP;
std::string Callbacks::deviceName_HFP;

bool Callbacks::isOkay = false;

///////////////////////////////////////////////////////////////////////////

void Callbacks::loop()
{
    if( nullptr == menu_ )
    {
        if( 0 == audMode )
        {
            set_Menu( Globals::menu_Main );
        }
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
    if( 1 == audMode )
    {
        menu_ = nullptr;

        Globals::tft.pushImage( 0, 0, Note_WIDTH, Note_HEIGHT, Note );
        Globals::tft.fillTriangle( 225, 55, 225, 65, 235, 60, TFT_WHITE );
        paintVolume( 219, 10 );
    }
    else if( 2 == audMode )
    {
        menu_ = nullptr;      

        Globals::tft.pushImage( 0, 0, Headset_WIDTH, Headset_HEIGHT, Headset );
        Globals::tft.fillTriangle( 5, 60, 15, 55, 15, 65, TFT_WHITE );
        paintVolume( 5, 10 );
    }
    else
    {
        ; // do nothing
    }    

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
    else if( 1 == audMode )
    {      
        volumeUp( micGain_A2DP );
    }
    else if( 2 == audMode )
    {      
        volumeUp( micGain_HFP );
    }
    else
    {
        ;   // do nothing        
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
    else if( 1 == audMode )
    {      
        volumeDown( micGain_A2DP );
    }
    else if( 2 == audMode )
    {      
        volumeDown( micGain_HFP );
    }
    else
    {
        ;   // do nothing        
    }
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::button_LEFT( Button2& btn )
{
    static_cast<void>( btn );

    if( nullptr == menu_ )
    {    
        Globals::commander.set_AUDROUTE__A2DP();
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

    if( nullptr == menu_ )
    {
        Globals::commander.set_AUDROUTE__HFP();
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
    Globals::commander.disconnect();
    Globals::commander.req_SCAN();
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
    Globals::commander.disconnect();
    Globals::commander.pair( pairedList.at( 0 ).macAddress().c_str() );
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////
 
void Callbacks::Menu_PreviousConnections_1()
{
    Globals::commander.disconnect();
    Globals::commander.pair( pairedList.at( 1 ).macAddress().c_str() );
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_PreviousConnections_2()
{
    Globals::commander.disconnect();
    Globals::commander.pair( pairedList.at( 2 ).macAddress().c_str() );
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_PreviousConnections_3()
{
    Globals::commander.disconnect();
    Globals::commander.pair( pairedList.at( 3 ).macAddress().c_str() );
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_PreviousConnections_BACK()
{
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Scanned_0()
{
    Globals::commander.pair( scanList.at( 0 ).macAddress().c_str() );
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////
 
void Callbacks::Menu_Scanned_1()
{
    Globals::commander.pair( scanList.at( 1 ).macAddress().c_str() );
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Scanned_2()
{
    Globals::commander.pair( scanList.at( 2 ).macAddress().c_str() );
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Scanned_3()
{
    Globals::commander.pair( scanList.at( 3 ).macAddress().c_str() );
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Scanned_BACK()
{
    set_Menu( Globals::menu_Main );
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_Delete__Delete()
{
    Globals::commander.set_AUDROUTE__None();
    Globals::commander.clr_PLIST();
    Globals::commander.req_PLIST();
    deviceName_A2DP.clear();
    deviceName_HFP.clear();

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
    if( false == isOkay )
    {
        // just connected to module, setup its defaults ...................
        Globals::commander.defaults();
        set_Menu( Globals::menu_Main );
    }

    isOkay = true;
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_ERR()
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_A2DP_Connected( const bool isConnected )
{
    isConnected_A2DP = isConnected;

    if( isConnected_A2DP )
    {
        Globals::commander.set_AUDROUTE__A2DP();
    }
    else if( isConnected_HFP )
    {
        ; // do nothing, at least one connected
    }
    else
    {
        Globals::commander.set_AUDROUTE__None();
    }

    Status::refresh();
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_A2DP_Device( const std::string& name )
{
    deviceName_A2DP = name;   
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_A2DP_MicGain( const int val )
{
    micGain_A2DP = val;
    Status::refresh();        
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_AUDMODE( const int val )
{
    audMode = val;

    if( 1 == audMode )
    {
        clr_Menu();
    }
    else if( 2 == audMode )
    {
        clr_Menu();
    }
    else if( nullptr == menu_ )
    {

        set_Menu( Globals::menu_Main );
    }    
    else
    {
        ; // do nothing
    }

    Status::refresh();
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_AUDROUTE( const int val )
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_HFP_Connected( const bool isConnected )
{
    isConnected_HFP = isConnected;

    if( !isConnected_HFP && !isConnected_A2DP )
    {
        Globals::commander.set_AUDROUTE__None();
    }

    Status::refresh();
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_HFP_Device( const std::string& name )
{
    deviceName_HFP = name;
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::on_HFP_MicGain( const int val )
{
    micGain_HFP = val;
    Status::refresh();
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

void Callbacks::volumeUp( int& vol )
{
    vol++;

    if( vol > 15 )
    {
        vol = 15;
    }

    volumeSend();
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::volumeDown( int& vol )
{
    vol--;

    if( vol < 0 )
    {
        vol = 0;
    }

    volumeSend();
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::volumeSend()
{
    Globals::commander.set_MICGAIN( micGain_A2DP, micGain_HFP );
    Globals::commander.get_MICGAIN();    
}

///////////////////////////////////////////////////////////////////////////
