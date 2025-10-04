#ifndef Menu_PreviousConnections_H
#define Menu_PreviousConnections_H

#include "Menu.h"

class Menu_PreviousConnections : public Menu
{
public:
    Menu_PreviousConnections( TFT_eSPI& tft );
    void Start();
};

#endif