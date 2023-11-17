#include "Settings.hpp"

Settings::Settings() : themeIndex(ThemeData::ThemeIndexDefault)
{
    this->gameSettings = new GameSettings();
}

Settings::~Settings() {
}

void Settings::setThemeIndex(const ThemeIndex themeIndex) {
    this->themeIndex = themeIndex;
}

void Settings::setGameSettings(const GameSettings gameSettings) {
    *this->gameSettings = gameSettings;
}

const ThemeIndex Settings::getThemeIndex() const {
    return this->themeIndex;
}

const GameSettings* Settings::getGameSettings() const {
    return this->gameSettings;
}