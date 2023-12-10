#include <Arduino.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>

#include <radio.h>

// all possible radio chips included.
#include <RDA5807M.h>

#include <RDSParser.h>

#include "setting.hpp"
#include "logger.h"
#include "menu.h"

// display
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT,
                         OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);
// radio
RDA5807M radio;

// menu
Menu m{NULL};
// web server
WebServer server(80);

/**
 * @brief Init radio
 *
 */
void radionInit()
{
    loging("Radio init");

    if (logging_on)
    {
        radio.debugEnable(true);
        radio._wireDebug(false);
    }

    radio.setup(RADIO_FMSPACING, RADIO_FMSPACING_100);  // for EUROPE
    radio.setup(RADIO_DEEMPHASIS, RADIO_DEEMPHASIS_50); // for EUROPE
    // Initialize the Radio

    Wire.begin(12, 13);
    if (!radio.initWire(Wire))
    {
        Serial.println("no radio chip found.");
        delay(4000);
        ESP.restart();
    };

    // Set all radio setting to the fixed values.
    radio.setBandFrequency(FIX_BAND, FIX_STATION);
    radio.setVolume(FIX_VOLUME);
    radio.setMono(false);
    radio.setMute(false);

    radio.setFrequency(FIX_STATION);
}

// variables used by interrupt service routines
int counter = 0;
int aState;
int aLastState;
int reduction = 0;

/**
 * @brief Interrupt service routine for encoder
 *
 */
void ICACHE_RAM_ATTR encoderISR() // interrupt service routines need to be in ram
{
    aState = digitalRead(PIN_A); // Reads the "current" state of the outputA
    // If the previous and the current state of the outputA are different, that means a Pulse has occured
    if (aState != aLastState)
    {
        // If the outputB state is different to the outputA state, that means the encoder is rotating clockwise
        if (digitalRead(PIN_B) != aState)
        {
            m.incSelected_item();
        }
        else
        {
            m.decSelected_item();
        }
    }
    aLastState = aState;
}
/**
 * @brief Interrupt service routine for encoder button
 *
 */
void IRAM_ATTR encoderButtonISR()
{
    if (m.selected){
        m.selected = 0;
    }
    else{
        m.selected = 1;
    }
    m.update = true;
}

///////////////////////////////WEB SERVER ENDPOINTS ///////////////////////////////////////
void WSRoot()
{
    String zprava =
        "<!DOCTYPE HTML>"
        "<html>"
        "<head> <meta charset='utf-8'> </head> <style> a{display:inline-block;padding:10px 20px;text-decoration:none;font-size:16px;font-weight:700;color:#fff;background-color:#3498db;border-radius:5px;transition:background-color .3s}a:hover{background-color:#2980b9}a:active{background-color:#1f6692}</style> <body>";

    zprava += "<h1>Dálkové ovládaní radia</h1>";
    zprava += "Volume ";
    zprava += m.volume;
    zprava += " : <a href=\"/volumeup\"> + </a>";
    zprava += " <a href=\"/volumedown\"> - </a>";
    zprava += " <br> vybraný index oblibené stanice: ";
    zprava += m.fav_stattion_c;
    zprava += "<input type=\"text\" id=\"numberInput\" placeholder=\"Číslo\">\n"
              " <a href=\"#\" onclick=\"redirectToFavorite()\">Přejít na oblíbenou stránku</a>";
    zprava += " <br><a href=\"/basson\"> Nastavit bassboost </a>";
    zprava += " <br><a href=\"/bassoff\"> Vypnout bassboost </a>";
    zprava += "<script> function redirectToFavorite(){var e=document.getElementById(\"numberInput\").value;isNaN(e)?alert(\"Zadejte platné čislo.\"):window.location.href=\"favorite?id=\"+encodeURIComponent(e)}</script>";
    zprava += "</body> </html>";
    server.send(200, "text/html", zprava);
}

void volumeUp()
{
    m.volume++;
    WSRoot();
    m.update = true;
}

void volumeDown()
{
    m.volume--;
    m.update = true;
    WSRoot();
}

void WSfavorite()
{

    if (server.hasArg("id"))
    {
        int index = atoi(server.arg("id").c_str());
        m.setFavoriteStation(index);
    }
    WSRoot();
}

void basson()
{
    m.setbassBoost(true);
    WSRoot();
}

void bassoff()
{
    m.setbassBoost(false);
    WSRoot();
}

///////////////////////////////WEB SERVER ENDPOINTS END ///////////////////////////////////////

void setup()
{
    Serial.begin(115000);
    logger_init();

    if (!display.begin(SSD1306_SWITCHCAPVCC))
    {
        FATAL_ERROR("SSD1306 allocation failed");
    }

    display.clearDisplay();
    display.display();

    radionInit();

    // encoder init
    pinMode(PLUS, OUTPUT);
    pinMode(PIN_A, INPUT);
    pinMode(PIN_B, INPUT);
    pinMode(BUTTON, INPUT_PULLUP);
    digitalWrite(PLUS, HIGH);
    aLastState = digitalRead(PIN_A);

    attachInterrupt(digitalPinToInterrupt(PIN_A), encoderISR, CHANGE);       // call encoderISR()       every high->low or low->high changes
    attachInterrupt(digitalPinToInterrupt(BUTTON), encoderButtonISR, ONLOW); // call encoderButtonISR() every high->low              changes

    m.setDisplay(&display);
    m.setRadio(&radio);
    radio.setVolume(1);

    // wifi
    WiFi.begin(wifiSSID, wifiPass);
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
    }
    loging("Ip addres is: %s", WiFi.localIP().toString());

    // web server
    server.on("/", WSRoot);
    server.on("/volumeup", volumeUp);
    server.on("/volumedown", volumeDown);
    server.on("/basson", basson);
    server.on("/bassoff", bassoff);
    server.on("/favorite", HTTP_GET, WSfavorite);
    server.begin();
}

/*Tests if radio gives right data to CLI*/
void testRadio()
{
    char s[12];
    radio.formatFrequency(s, sizeof(s));
    Serial.print("Station:");
    Serial.println(s);

    Serial.print("Radio:");
    radio.debugRadioInfo();

    Serial.print("Audio:");
    radio.debugAudioInfo();
}

void loop()
{
    m.DisplayMenu();
    server.handleClient();
}