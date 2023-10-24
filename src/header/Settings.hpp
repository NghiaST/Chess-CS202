#ifndef __Settings_hpp__
#define __Settings_hpp__

#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "GameSettings.hpp"
#include "Theme.hpp"

struct Settings {
private:
    Theme theme;
    GameSettings gameSettings;
public:
    Settings();
    ~Settings();
    void setTheme(Theme theme);
    void setGameSettings(GameSettings gameSettings);
    Theme getTheme() const;
    GameSettings getGameSettings() const;
};

#endif