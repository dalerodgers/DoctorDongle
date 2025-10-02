#ifndef Pins_H
#define Pins_H

#include <stdint.h>

namespace Pins
{
    static constexpr uint8_t ADC_EN = 14;  //ADC_EN is the ADC detection enable port
    static constexpr uint8_t ADC_PIN = 34;

    static constexpr uint8_t BUTTON_1 = 35;
    static constexpr uint8_t BUTTON_2 = 0;

    static constexpr uint8_t BT_LED = 36;
    
    static constexpr uint8_t SERIAL_TX = 22;
    static constexpr uint8_t SERIAL_RX = 21;
}

#endif
