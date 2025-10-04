#ifndef Menu_Scanned_H
#define Menu_Scanned_H

#include "Menu.h"

class Menu_Scanned : public Menu
{
public:
    Menu_Scanned( TFT_eSPI& tft );
    void Start();
};

#endif