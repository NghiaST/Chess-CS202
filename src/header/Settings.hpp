#ifndef __Settings_hpp__
#define __Settings_hpp__

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "GameSettings.hpp"
#include "Theme.hpp"

class Settings {
private:
    Theme* theme;
    GameSettings* gameSettings;
public:
    Settings();
    ~Settings();
    void setTheme(const Theme theme);
    void setGameSettings(const GameSettings gameSettings);
    const Theme* getTheme() const;
    const GameSettings* getGameSettings() const;
};

#endif