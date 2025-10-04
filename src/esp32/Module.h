#ifndef Module_H
#define Module_H

#include <stdint.h>

class Module
{
public:
    static void initialise();
    static void loop();

private:
    static unsigned long flashTimer_;
    static uint32_t flashColour_;
};

#endif