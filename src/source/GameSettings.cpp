#include "GameSettings.hpp"

GameSettings::GameSettings() {
    firstturn = 0;
    time = 600;
    mode = 0;
    difficulty = 0;
}

GameSettings::~GameSettings() {}

void GameSettings::setFirstTurn(int firstturn) {
    this->firstturn = firstturn;
}

void GameSettings::setTime(int time) {
    this->time = time;
}

void GameSettings::setMode(int mode) {
    this->mode = mode;
}

void GameSettings::setDifficulty(int difficulty) {
    this->difficulty = difficulty;
}

int GameSettings::getFirstTurn() {
    return firstturn;
}

int GameSettings::getTime() {
    return time;
}

int GameSettings::getMode() {
    return mode;
}

int GameSettings::getDifficulty() {
    return difficulty;
}

