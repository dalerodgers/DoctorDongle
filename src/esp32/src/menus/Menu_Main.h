#ifndef Menu_Main_H
#define Menu_Main_H

#include "Menu.h"

class Menu_Main : public Menu
{
public:
    Menu_Main( TFT_eSPI& tft );
    void Start();
};

#endif