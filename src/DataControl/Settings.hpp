#ifndef __Settings_hpp__
#define __Settings_hpp__

#include "GameSettings.hpp"
#include "Theme.hpp"
#include <SFML/Graphics.hpp>

class Settings {
private:
    ThemeIndex themeIndex;
    GameSettings* gameSettings;
public:
    Settings();
    ~Settings();
    void setThemeIndex(const ThemeIndex themeIndex);
    void setGameSettings(const GameSettings gameSettings);
    const ThemeIndex getThemeIndex() const;
    const GameSettings* getGameSettings() const;
};

#endif