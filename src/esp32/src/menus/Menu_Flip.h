#ifndef Menu_Flip_H
#define Menu_Flip_H

#include "Menu.h"

class Menu_Flip : public Menu
{
public:
    Menu_Flip( TFT_eSPI& tft );
    void Start();
};

#endif