
#include "menu.h"

void Menu::DisplayRandomText(const char *c, unsigned size, u_int8_t color, u_int8_t cursor_x, u_int8_t cursor_y)
{
    display->setTextSize(size);
    display->setTextColor(color);
    display->setCursor(cursor_x, cursor_y);
    display->println(c);
    display->display();

    loging("Printing text on display: \" %s \"", c);
}

Menu::Menu(Adafruit_SSD1306 *display)
{
    display = display;
}

void Menu::DisplayMenu()
{
    if (!update)
    {
        return;
    }
    update = false;

    display->clearDisplay();

    loging("Displaying menu selected: %d, selected: %d", selected_item, selected);

    displayMenuItems();
    switch (selected_item)
    {
    case 0:
        loging("Selected radio station manualy: %d", radiofreq);
        DisplayRadioTab();
        updateRadioFreq();
        break;
    case 1:
        loging("Selected radion from favorite %d", favorite_station[fav_stattion_c]);
        DisplayFavoriteTab();

        updateRadioFav();
        break;
    case 2:
        DisplayVolumeTab();
        updateRadioVolume();
        break;
    default:
        break;
    }
}

void Menu::displayMenuItems()
{
    std::string out;
    for (std::string s : menu_items)
    {
        if (s == menu_items[selected_item])
        {
            std::transform(s.begin(), s.end(), s.begin(), ::toupper);
            out.append(s);
        }
        else
        {
            out.append(s);
        }
        out.append(" ");
    }

    // out.append(std::to_string(selected_item)); // for debugging menu
    DisplayRandomText(out.c_str(), 1, SSD1306_WHITE, 0, 0);
    if (selected)
        display->fillRoundRect(0, 10, 128, 4, 0, SSD1306_WHITE);
    display->fillRoundRect(0, 10, 128, 1, 0, SSD1306_WHITE);
}

void Menu::DisplayRadioTab()
{
    auto s = std::to_string(radiofreq / 100.0);
    s = s.substr(0, 5);
    DisplayRandomText(s.c_str(), 4, SSD1306_WHITE, 0, 14);
}

void Menu::DisplayFavoriteTab()
{
    auto s = std::to_string(favorite_station[fav_stattion_c] / 100.0);
    s = s.substr(0, 5);

    DisplayRandomText(s.c_str(), 4, SSD1306_WHITE, 0, 14);

    auto c = std::string("Favorite station: ");
    c.append(std::to_string(fav_stattion_c));

    DisplayRandomText(c.c_str(), 1, SSD1306_WHITE, 0, 55);
}

void Menu::DisplayVolumeTab()
{
    auto s = std::to_string(volume);
    DisplayRandomText(s.c_str(), 4, SSD1306_WHITE, 10, 14);
}

void Menu::incSelected_item()
{
    update = true;

    if (selected)
    {
        switch (selected_item)
        {
        case 0:
            radiofreq += 10;
            break;
        case 1:
            fav_stattion_c++;
            if (fav_stattion_c >= 10)
            {
                fav_stattion_c = 0;
            }

            break;
        case 2:
            volume++;
            if (volume < 0)
            {
                volume = 0;
            }
            break;
        default:
            break;
        }
    }
    else
    {
        selected_item++;
        if (selected_item == menu_items.size())
        {
            selected_item = 0;
        }
    }
}

void Menu::decSelected_item()
{
    update = true;

    if (selected)
    {
        switch (selected_item)
        {
        case 0:
            radiofreq -= 10;
            break;
        case 1:
            fav_stattion_c--;
            if (fav_stattion_c < 0)
            {
                fav_stattion_c = 9;
            }

            break;
        case 2:
            volume--;
            if (volume < 0)
            {
                volume = 0;
            }
            break;
        default:
            break;
        }
    }
    else
    {
        selected_item--;

        if (selected_item < 0)
        {
            selected_item = menu_items.size() - 1;
        }
    }
};

void Menu::updateRadioFav()
{
    radio->setFrequency(favorite_station[fav_stattion_c]);
}
void Menu::updateRadioVolume()
{
    radio->setVolume(volume);
}
void Menu::updateRadioFreq()
{
    radio->setFrequency(radiofreq);
}

void Menu::setFavoriteStation(int index)
{
    loging("Setting index of favorite station: %d", index);
    selected_item = 1;
    update = true;
    radio->setFrequency(favorite_station[index]);
    fav_stattion_c = index;
}