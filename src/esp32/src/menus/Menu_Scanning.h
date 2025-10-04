#ifndef Menu_Scanning_H
#define Menu_Scanning_H

#include "Menu.h"

class Menu_Scanning : public Menu
{
public:
    Menu_Scanning( TFT_eSPI& tft );
    void Start();
};

#endif