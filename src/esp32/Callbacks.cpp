#include "Callbacks.h"

#include "Globals.h"

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

///////////////////////////////////////////////////////////////////////////

void Callbacks::loop()
{
    if( nullptr == menu_ )
    {
        ;   // do nothing
    }
    else if( (millis() - lastButtonPress_ ) < 10000 )
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
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::clr_Menu()
{
    menu_ = nullptr;
    Globals::tft.fillScreen( TFT_BLUE );
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
}

///////////////////////////////////////////////////////////////////////////
 
void Callbacks::Menu_PreviousConnections_1()
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_PreviousConnections_2()
{
}

///////////////////////////////////////////////////////////////////////////

void Callbacks::Menu_PreviousConnections_3()
{
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

void Callbacks::OnScanned( std::vector<Device>& list )
{
    if( &Globals::menu_Scanning == menu_ )
    {  
        scanList = list;
        set_Menu( Globals::menu_Scanned );
    }
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