#ifndef Status_H
#define Status_H

class Status
{
public:
    static void initialise();
    static void loop();

    static void refresh();

private:
    static bool lastLedState_;
    static unsigned long lastBatteryTime_;
    static int vref_;

    static void paint_LED( const bool led );
    static void paint_Device();
    static void paint_ADC();
};

#endif