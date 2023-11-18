#include <DataControl/GameAttributes.hpp>
#include <DataControl/FileInit.hpp>

GameAttributes::GameAttributes() {
    this->mode = 0;
    this->level = 0;
    this->timeWhite = 0;
    this->timeBlack = 0;
    this->isBotHelp = false;
    this->isPlayerWhite = true;
    this->isCountDown = false;
    Loading();
}

GameAttributes::GameAttributes(int mode, int level, int timeWhite, int timeBlack, bool isBotHelp, bool isPlayerWhite) {
    this->mode = mode;
    this->level = level;
    this->timeWhite = timeWhite;
    this->timeBlack = timeBlack;
    this->isBotHelp = isBotHelp;
    this->isPlayerWhite = isPlayerWhite;
    this->isCountDown = false;
}

GameAttributes::~GameAttributes() {}

void GameAttributes::NewLoading() {
    FileInit::LoadOptions(mode, level, isBotHelp); //, timeWhite, timeBlack);
    timeWhite = 120000;
    timeBlack = 120000;
    Fresh();
}

void GameAttributes::Loading() {
    FileInit::LoadOptions(mode, level, isBotHelp);
    Fresh();
}

void GameAttributes::Fresh() {
    if (mode == 1) {
        isPlayerWhite = false;
        level = 0;
    }
    else
        isPlayerWhite = true;
    
    isCountDown = false;
}

void GameAttributes::switchTurn() {
    UpdateTime();
    isWhiteTurn = !isWhiteTurn;
    isCountDown = true;
}

void GameAttributes::setTurn(bool isWhiteTurn) {
    UpdateTime();
    this->isWhiteTurn = isWhiteTurn;
}

void GameAttributes::UpdateTime() {
    if (isCountDown) {
        sf::Time deltaTime = clock.getElapsedTime();
        if (isWhiteTurn) {
            timeWhite -= deltaTime.asMilliseconds();
            if (timeWhite < 0) timeWhite = 0;
        }
        else {
            timeBlack -= deltaTime.asMilliseconds();
            if (timeBlack < 0) timeBlack = 0;
        }
    } 
    clock.restart();
}

bool GameAttributes::isOutOfTime() const {
    if (isWhiteTurn)
        return timeWhite <= 0;
    else
        return timeBlack <= 0;
}

bool GameAttributes::isOutOfTime(bool isWhite) const
{
    if (isWhite)
        return timeWhite <= 0;
    else
        return timeBlack <= 0;
}

bool GameAttributes::IsCountDown() const {
    return isCountDown;
}

bool GameAttributes::IsWhiteTurn() const {
    return isWhiteTurn;
}

int GameAttributes::getCurrentTime() const {
    if (isWhiteTurn)
        return timeWhite;
    else
        return timeBlack;
}

int GameAttributes::getTime(bool isWhite) const {
    if (isWhite)
        return timeWhite;
    else
        return timeBlack;
}

void GameAttributes::setCountDown(bool isCountDown) {
    this->isCountDown = isCountDown;
    clock.restart();
}
