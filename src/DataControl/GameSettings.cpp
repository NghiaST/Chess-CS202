#include <DataControl/GameSettings.hpp>
#include <DataControl/FileInit.hpp>

GameSettings::GameSettings() {
    this->mode = 0;
    this->difficulty = 0;
    this->timeMode = 0;
}

GameSettings::GameSettings(int mode, int difficulty, int timeMode, int extraTime, bool isTime, bool isWhite, bool isBotHelp) {
    this->mode = mode;
    this->difficulty = difficulty;
    this->timeMode = timeMode;
    this->isTime = isTime;
    this->isWhite = isWhite;
    this->isBotHelp = isBotHelp;
}

GameSettings::~GameSettings() {}

// Modifiers
void GameSettings::setMode(int mode) {
    this->mode = mode;
}

void GameSettings::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
}

void GameSettings::setTimeMode(int timeMode) {
    this->timeMode = timeMode;
}

void GameSettings::setIsTime(bool isTime) {
    this->isTime = isTime;
}

void GameSettings::setIsWhite(bool isWhite) {
    this->isWhite = isWhite;
}

void GameSettings::setIsBotHelp(bool isBotHelp) {
    this->isBotHelp = isBotHelp;
}

// Accessors
int GameSettings::getMode() const {
    return this->mode;
}

int GameSettings::getDifficulty() const {
    return this->difficulty;
}

int GameSettings::getTimeTotal() const {
    return this->TimeTotal[this->timeMode];
}

int GameSettings::getTimeExtra() const {
    return this->TimeExtra[this->timeMode];
}

bool GameSettings::getIsTime() const {
    return this->isTime;
}

bool GameSettings::getIsWhite() const {
    return this->isWhite;
}

bool GameSettings::getIsBotHelp() const {
    return this->isBotHelp;
}