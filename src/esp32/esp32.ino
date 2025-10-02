#include <TFT_eSPI.h>
#include <esp_adc_cal.h>

#include "Menu.h"
#include "driver/rtc_io.h"

#include "Button2.h"
#include "Menu_Main.h"
#include "Callbacks.h" 
#include "Globals.h"
#include "Status.h"

#define ADC_EN              14  //ADC_EN is the ADC detection enable port
#define ADC_PIN             34
#define BUTTON_1            35
#define BUTTON_2            0

//TFT_eSPI tft = TFT_eSPI(135, 240); // Invoke custom library
Button2 button_UP( BUTTON_1 );
Button2 button_DOWN( BUTTON_2 );

char buff[512];
int vref = 1100;

//static Menu mainMenu( tft );
///static Menu_Main menu_Main( tft );

//void showVoltage()
//{
//    static uint64_t timeStamp = 0;
//    if (millis() - timeStamp > 1000) {
//        timeStamp = millis();
//        uint16_t v = analogRead(ADC_PIN);
//        float battery_voltage = ((float)v / 4095.0) * 2.0 * 3.3 * (vref / 1000.0);
//        String voltage = "Voltage :" + String(battery_voltage) + "V";
//        Serial.println(voltage);
//        //tft.fillScreen(TFT_BLACK);
//        //tft.setTextDatum(MC_DATUM);
//        //tft.drawString(voltage,  tft.width() / 2, tft.height() / 2 );
//    }
//}

void setup()
{
    Serial.begin(115200);
    Serial.println("Start");

    Status::initialise();

    /*
    ADC_EN is the ADC detection enable port
    If the USB port is used for power supply, it is turned on by default.
    If it is powered by battery, it needs to be set to high level
    */
    //pinMode(ADC_EN, OUTPUT);
    //digitalWrite(ADC_EN, HIGH);

    Globals::tft.init();
    Globals::tft.setRotation(1);

    esp_adc_cal_characteristics_t adc_chars;
    esp_adc_cal_value_t val_type = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN_DB_11, ADC_WIDTH_BIT_12, 1100, &adc_chars);    //Check type of calibration value used to characterize ADC
    if (val_type == ESP_ADC_CAL_VAL_EFUSE_VREF) {
        Serial.printf("eFuse Vref:%u mV", adc_chars.vref);
        vref = adc_chars.vref;
    } else if (val_type == ESP_ADC_CAL_VAL_EFUSE_TP) {
        Serial.printf("Two Point --> coeff_a:%umV coeff_b:%umV\n", adc_chars.coeff_a, adc_chars.coeff_b);
    } else {
        Serial.println("Default Vref: 1100mV");
    }

    button_UP.setClickHandler( &Callbacks::button_UP );
    button_UP.setDoubleClickHandler( &Callbacks::button_ENTER );

    button_DOWN.setClickHandler( &Callbacks::button_DOWN );
    button_DOWN.setDoubleClickHandler( &Callbacks::button_ENTER );

    std::vector<Device> eric;
    eric.push_back( { "Sea of Tranquility", "12345678" } );
    eric.push_back( { "Bob the dooley", "ABCDEFGH" } );
    Globals::callbacks.on_PairedList( eric );

    Callbacks::clr_Menu();
}

void loop()
{
    button_UP.loop();
    button_DOWN.loop();

    Callbacks::loop();
    Status::loop();
}
