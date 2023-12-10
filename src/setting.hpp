#ifndef SETTING_HPP
#define SETTING_HPP


// radio settings
#define FIX_BAND RADIO_BAND_FM  ///< The band that will be tuned by this sketch is FM.
#define FIX_STATION 9900        ///< The station that will be tuned by this sketch is 89.30 MHz.
#define FIX_VOLUME 10           ///< The volume that will be set by this sketch is level 4.
#define DEF_VOLUME 1

#define logging_on 1


// display stuff
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

#define OLED_MOSI 23
#define OLED_CLK 18
#define OLED_DC 27
#define OLED_CS 5
#define OLED_RESET 16


// encoder 

#define PIN_A   26 //ky-040 clk pin, interrupt & add 100nF/0.1uF capacitors between pin & ground!!!
#define PIN_B   25 //ky-040 dt  pin,             add 100nF/0.1uF capacitors between pin & ground!!!
#define BUTTON  17 //ky-040 sw  pin, interrupt & add 100nF/0.1uF capacitors between pin & ground!!!
#define PLUS 14 // ky-040 plus PIN 
// gnd si connected to board GND


// wifi

#define wifiSSID "medlanky-net"
#define  wifiPass "hovnocuc"

#endif // SETTING_HPP