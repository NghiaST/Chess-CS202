#include "TimeButton.hpp"

TimeButton::TimeButton(int id, Point renderPositionWhite, Point renderPositionBlack, Point renderSize, const sf::Font* font, const ColorButMulti& colorButMulti) {
    this->renderPositionWhite = renderPositionWhite;
    this->renderPositionBlack = renderPositionBlack;

    isReverseTable = false;
    isWhiteTurn = true;
    isCountDown = false;
    timeWhite = -1;
    timeBlack = -1;

    buttonWhite = new Button(id, renderPositionWhite, renderSize, false, true, font, colorButMulti, 20, "00:00");
    buttonBlack = new Button(id, renderPositionBlack, renderSize, false, true, font, colorButMulti, 20, "00:00");
}

TimeButton::~TimeButton() {
    delete buttonWhite;
    delete buttonBlack;
}

void TimeButton::setReverseTable(bool isReverseTable) {
    this->isReverseTable = isReverseTable;
    if (isReverseTable) {
        buttonWhite->setRenderPosition(renderPositionBlack);
        buttonBlack->setRenderPosition(renderPositionWhite);
    }
    else {
        buttonWhite->setRenderPosition(renderPositionWhite);
        buttonBlack->setRenderPosition(renderPositionBlack);
    }
}

std::string TimeButton::update(sf::Time deltaTime) {
    return "";
}

void TimeButton::update(GameAttributes &gameAttributes) {
    if (gameAttributes.isOutOfTime()) {
        timeWhite = -1;
        timeBlack = -1;
    }
    else {
        timeWhite = gameAttributes.getTime(true) / 1000.0;
        timeBlack = gameAttributes.getTime(false) / 1000.0;
    }
    isWhiteTurn = gameAttributes.IsWhiteTurn();
    isCountDown = gameAttributes.IsCountDown();
    updateRender();
}

void TimeButton::setTime(int timeWhite, int timeBlack) {
    this->timeWhite = timeWhite / 1000.0;
    this->timeBlack = timeBlack / 1000.0;
    updateRender();
}

void TimeButton::updateRender() {
    auto ProcessStr = [&](Button* buttonSide, double time, bool isRuntime) -> void {
        std::string str = std::to_string((int)time / 60) + ":" + ((int)time % 60 < 10 ? "0" : "") + std::to_string((int)time % 60);
        if (time < 60) {
            str += "." + std::to_string((int)(time * 10) % 10);
        }
        if (time < 0) {
            str = "--:--";
        }
        buttonSide->setText(str);
        buttonSide->setButtonState((ButtonStates) (isRuntime ? 3 : 0));
    };

    ProcessStr(buttonWhite, timeWhite, isCountDown && isWhiteTurn);
    ProcessStr(buttonBlack, timeBlack, isCountDown && !isWhiteTurn);
}

void TimeButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*buttonWhite);
    target.draw(*buttonBlack);
}

void TimeButton::setColorBM(const ColorButMulti &colorButMulti) {
    buttonWhite->setColorBM(colorButMulti);
    buttonBlack->setColorBM(colorButMulti);

    updateRender();
}

void TimeButton::setTurn(bool isWhiteturn) {
    this->isWhiteTurn = isWhiteturn;

    updateRender();
}

void TimeButton::setIsCountDown(bool isCountDown) {
    this->isCountDown = isCountDown;

    updateRender();
}

void TimeButton::changeTurn() {
    isWhiteTurn ^= 1;
    isCountDown = true;
}

void TimeButton::reset() {
    isWhiteTurn = true;
    isCountDown = false;
    timeWhite = -1;
    timeBlack = -1;
    updateRender();
}