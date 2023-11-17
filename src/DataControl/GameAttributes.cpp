#include "GameAttributes.hpp"
#include "FileInit.hpp"

GameAttributes::GameAttributes() {
    this->mode = 0;
    this->level = 0;
    this->timeWhite = 0;
    this->timeBlack = 0;
    this->isBotHelp = false;
    this->isPlayerWhite = true;
}

GameAttributes::GameAttributes(int mode, int level, int timeWhite, int timeBlack, bool isBotHelp, bool isPlayerWhite) {
    this->mode = mode;
    this->level = level;
    this->timeWhite = timeWhite;
    this->timeBlack = timeBlack;
    this->isBotHelp = isBotHelp;
    this->isPlayerWhite = isPlayerWhite;
}

GameAttributes::~GameAttributes() {}

void GameAttributes::Loading() {
    FileInit::LoadOptions(mode, level, isBotHelp); //, timeWhite, timeBlack, isBotHelp);
    Fresh();
}

void GameAttributes::Fresh() {
    if (mode == 1) {
        isPlayerWhite = false;
        level = 0;
    }
    else
        isPlayerWhite = true;
    
    timeWhite = 120 * 1000;
    timeBlack = 120 * 1000;
}

bool GameAttributes::IsOutOfTime(bool isWhite) const {
    if (isWhite)
        return timeWhite <= 0;
    else
        return timeBlack <= 0;
}
