#ifndef Callbacks_H
#define Callbacks_H

#include "src/menus/Menu.h"
#include "src/common/Device.h"
#include "src/common/Receiver.h"

class Button2;

class Callbacks : public Receiver::RequiredIf
{
public:
    static void loop();

    static void set_Menu( Menu& menu );
    static void clr_Menu();

    static void button_UP( Button2& btn );
    static void button_DOWN( Button2& btn );
    static void button_LEFT( Button2& btn );
    static void button_RIGHT( Button2& btn );
    static void button_ENTER( Button2& btn );

    static void Menu_Main__PreviousConnections();
    static void Menu_Main__ScanForNew();
    static void Menu_Main__DeleteAll();
    static void Menu_Main__BACK();

    static void Menu_Scanning__BACK();

    static void Menu_PreviousConnections_0();
    static void Menu_PreviousConnections_1();
    static void Menu_PreviousConnections_2();
    static void Menu_PreviousConnections_3();
    static void Menu_PreviousConnections_BACK();

    static const Menu::FuncPtr Menu_PreviousConnections_N[Menu::MAX_OPTIONS];

    static void Menu_Scanned_0();
    static void Menu_Scanned_1();
    static void Menu_Scanned_2();
    static void Menu_Scanned_3();
    static void Menu_Scanned_BACK();

    static const Menu::FuncPtr Menu_Scanned_N[Menu::MAX_OPTIONS];

    static void Menu_Delete__Delete();
    static void Menu_Delete__BACK();    

    static std::vector<Device> pairedList;
    static std::vector<Device> scanList;

    static bool isConnected_A2DP;
    static bool isConnected_HFP;

    static int micGain_A2DP;
    static int micGain_HFP;

    static std::string deviceName;
    
public://protected:
    virtual void on_OK() override;
    virtual void on_ERR() override;

    virtual void on_A2DP_Connected( const bool isConnected ) override;
    virtual void on_A2DP_Device( const std::string& deviceName ) override;
    virtual void on_A2DP_MicGain( const int val ) override;
    virtual void on_AUDROUTE( const std::string& val ) override;
    virtual void on_HFP_Connected( const bool isConnected ) override;
    virtual void on_HFP_Device( const std::string& deviceName ) override;
    virtual void on_HFP_MicGain( const int val ) override;
    virtual void on_PairedList( const std::vector<Device>& deviceList ) override;
    virtual void on_ScanList( const std::vector<Device>& deviceList ) override;

private:
    static Menu* menu_;
    static unsigned long lastButtonPress_;

    static void paintVolume( const int32_t x, const int32_t y );    
};

namespace Globals
{
    extern Callbacks callbacks;
}

#endif