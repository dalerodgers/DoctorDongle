#ifndef Menu_Delete_H
#define Menu_Delete_H

#include "Menu.h"

class Menu_Delete : public Menu
{
public:
    Menu_Delete( TFT_eSPI& tft );
    void Start();
};

#endif