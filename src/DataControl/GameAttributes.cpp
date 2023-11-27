#include <DataControl/GameAttributes.hpp>
#include <DataControl/FileManager.hpp>

GameAttributes::GameAttributes(bool isLoad) {
    if (isLoad) NewLoading();
    else {
        this->variants = 0;
        this->mode = 0;
        this->level = 0;
        this->timeWhite = 0;
        this->timeBlack = 0;
        this->isBotHelp = false;
        this->isPlayerWhite = true;
        this->isCountDown = false;
    }
}

GameAttributes::GameAttributes(int variants, int mode, int level, int timeTotalMode, int timeExtraMode, bool isBotHelp) {
    this->variants = variants;
    this->mode = mode;
    this->level = level;
    this->timeTotalMode = timeTotalMode;
    this->timeExtraMode = timeExtraMode;
    this->isBotHelp = isBotHelp;
    this->isPlayerWhite = isPlayerWhite;
    this->isCountDown = false;
    this->timeWhite = (timeTotalMode == -1 ? -1 : TOTAL[timeTotalMode] * 1000);
    this->timeBlack = (timeTotalMode == -1 ? -1 : TOTAL[timeTotalMode] * 1000);
    Fresh();
}

GameAttributes::~GameAttributes() {}

void GameAttributes::NewLoading() {
    FileManager::LoadConfig(*this);
    timeWhite = timeBlack = TOTAL[timeTotalMode] * 1000;
    Fresh();
}

void GameAttributes::Loading() {
    FileManager::LoadConfig(*this);
    Fresh();
}

void GameAttributes::Fresh() {
    if (mode == 1) {
        isPlayerWhite = false;
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

void GameAttributes::updateMakeMove() {
    if (timeExtraMode == -1) return;
    if (isWhiteTurn) {
        timeWhite += EXTRA[timeExtraMode] * 1000;
    }
    else {
        timeBlack += EXTRA[timeExtraMode] * 1000;
    }
    switchTurn();
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

std::string GameAttributes::getVariantsName() const {
    return variantsName[variants];
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

// Accesors

int GameAttributes::getVariants() const {
    return variants;
}

int GameAttributes::getMode() const {
    return mode;
}

int GameAttributes::getLevel() const {
    return level;
}

int GameAttributes::getTimeTotalMode() const {
    return timeTotalMode;
}

int GameAttributes::getTimeExtraMode() const {
    return timeExtraMode;
}

bool GameAttributes::getIsBotHelp() const {
    return isBotHelp;
}

// Modifiers
void GameAttributes::setMode(int mode) {
    this->mode = mode;
    Fresh();
}