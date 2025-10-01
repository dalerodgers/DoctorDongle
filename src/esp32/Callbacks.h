#ifndef Callbacks_H
#define Callbacks_H

#include <string>
#include <vector>
#include "Menu.h"

class Button2;

struct Device
{
   std::string name;
   std::string macAddress;
};

class Callbacks
{
public:
    static void loop();

    static void set_Menu( Menu& menu );
    static void clr_Menu();

    static void button_UP( Button2& btn );
    static void button_DOWN( Button2& btn );
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

    static void OnScanned( std::vector<Device>& list );

    static std::vector<Device> pairedList;
    static std::vector<Device> scanList;

private:
    static Menu* menu_;
    static unsigned long lastButtonPress_;
};

#endif