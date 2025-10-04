#ifndef Pins_H
#define Pins_H

#include <stdint.h>

namespace Pins
{
    static constexpr uint8_t ADC_EN = 14;  //ADC_EN is the ADC detection enable port
    static constexpr uint8_t ADC_PIN = 34;

    static constexpr uint8_t BUTTON_1 = 35;
    static constexpr uint8_t BUTTON_2 = 0;

    static constexpr uint8_t JOY_A = 33;
    static constexpr uint8_t JOY_B = 12;
    static constexpr uint8_t JOY_C = 13;
    static constexpr uint8_t JOY_D = 15;
    static constexpr uint8_t JOY_E = 32;

    static constexpr uint8_t BT_LED = 25;
    
    static constexpr uint8_t SERIAL_TX = 22;
    static constexpr uint8_t SERIAL_RX = 21;
}

#endif
