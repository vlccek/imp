//
// Created by jvlk on 6.12.23.
//

#ifndef IMP_MENU_H
#define IMP_MENU_H

#include <Adafruit_SSD1306.h>
#include <Arduino.h>
#include <vector>
#include <string>
#include <string>
#include "logger.h"
#include <radio.h>
#include <RDA5807M.h>

/**
 * @brief Reprezentation of menu on display
 *
 */
class Menu
{
private:
    /**
     * @brief Display
     *
     */
    Adafruit_SSD1306 *display;

    /**
     * @brief Radio
     *
     */
    RDA5807M *radio = NULL;

    /**
     * @brief Menu items
     *
     */
    std::vector<std::string> menu_items = {"Radio", "Favorite", "Volume"};

    /**
     * @brief List of Favorite stations
     *
     */
    RADIO_FREQ favorite_station[10] = {
        9310,
        8950,
        9040,
        9100,
        9260,
        9310,
        9510,
        9550,
        9900,
        10550};

    /**
     * @brief Current radio freq
     *
     */
    RADIO_FREQ radiofreq = FIX_STATION;

    /**
     * @brief Display radio tab on display
     *
     */
    void DisplayRadioTab();

    /**
     * @brief Display favorite tab on display
     *
     */
    void DisplayFavoriteTab();

    /**
     * @brief Display volume tab on display
     *
     */
    void DisplayVolumeTab();

    /**
     * @brief Display menu items on display
     *
     */
    void displayMenuItems();

    /**
     * @brief Save station frequency to radio device
     *
     */
    void updateRadioFav();

    /**
     * @brief Save volume to radio device
     *
     */
    void updateRadioVolume();

    /**
     * @brief Save radio device frequency to variable
     *
     */
    void updateRadioFreq();

public:
    /**
     * @brief Construct a new Menu object
     *
     * @param display
     */
    Menu(Adafruit_SSD1306 *display);

    /**
     * @brief Get the Selected Item object
     *
     * @return int
     */
    int const getSelectedItem()
    {
        return selected_item;
    };

    /**
     * @brief Realize move in menu or settings
     *
     * @return RADIO_FREQ
     */
    void incSelected_item();

    /**
     * @brief Realize move in menu or settings
     *
     * @return RADIO_FREQ
     */
    void decSelected_item();

    /**
     * @brief Set the Display object
     *
     * @param display
     */
    void setDisplay(Adafruit_SSD1306 *display) { this->display = display; };

    /**
     * @brief Set the Radio object
     *
     * @param radio
     */
    void setRadio(RDA5807M *radio) { this->radio = radio; };

    /**
     * @brief Display menu on display
     *
     */
    void DisplayMenu();

    /**
     * @brief Display random text on display
     *
     * @param c
     * @param size
     * @param color
     * @param cursor_x
     * @param cursor_y
     */
    void DisplayRandomText(const char *c, unsigned size = 1, u_int8_t color = SSD1306_WHITE, u_int8_t cursor_x = 5,
                           u_int8_t cursor_y = 28);

    /**
     * @brief Set the to radio some of favorite station by index
     * @param index
     */
    void setFavoriteStation(int index);

    /**
     * @brief Set the volume to radio
     * @param volume
     */
    void setbassBoost(bool value) { radio->setBassBoost(value); };

    /**
     * @brief Get the favorite freq list
     *
     * @return RADIO_FREQ
     */
    RADIO_FREQ *getFavRadios() { return favorite_station; }

    /**
     * @brief Use as a flag for update display
     *
     * @return int
     */
    bool update = true;

    /**
     * @brief Use as a flag for save if some menu is saved
     *
     * @return int
     */
    bool selected = true;

    /**
     * @brief Use as tmp value for volume
     *
     * @return int
     */
    int volume = DEF_VOLUME;

    /**
     * @brief use for tracking position in menu
     */
    int selected_item = 0;

    /**
     * @brief curently selected favorite station
     */
    int fav_stattion_c = 0;

    inline void flipselected() { selected = selected ? false : true; };
};

/**
 * @brief Display text on display
 *
 * @param c
 * @param size
 * @param color
 * @param cursor_x
 * @param cursor_y
 */
void DisplayText(const char *c, unsigned size = 1, u_int8_t color = SSD1306_WHITE, u_int8_t cursor_x = 5, u_int8_t cursor_y = 28);

#endif // IMP_MENU_H
