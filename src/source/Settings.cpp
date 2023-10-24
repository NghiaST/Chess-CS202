#include "Settings.hpp"

Settings::Settings() {
}

Settings::~Settings() {
}

void Settings::setTheme(Theme theme) {
    this->theme = theme;
}

void Settings::setGameSettings(GameSettings gameSettings) {
    this->gameSettings = gameSettings;
}

Theme Settings::getTheme() const {
    return this->theme;
}

GameSettings Settings::getGameSettings() const {
    return this->gameSettings;
}