#include "Settings.hpp"

Settings::Settings() {
    this->theme = new Theme();
    this->gameSettings = new GameSettings();
}

Settings::~Settings() {
}

void Settings::setTheme(const Theme theme) {
    *this->theme = theme;
}

void Settings::setGameSettings(const GameSettings gameSettings) {
    *this->gameSettings = gameSettings;
}

const Theme* Settings::getTheme() const {
    return this->theme;
}

const GameSettings* Settings::getGameSettings() const {
    return this->gameSettings;
}