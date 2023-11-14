#include "TimeButton.hpp"

TimeButton::TimeButton(int id, Point renderPositionWhite, Point renderPositionBlack, Point renderSize, const sf::Font* font, const ColorButMulti& colorButMulti) {
    this->renderPositionWhite = renderPositionWhite;
    this->renderPositionBlack = renderPositionBlack;

    isReverseTable = false;
    isWhiteTurn = true;
    isCountDown = false;
    isOutOfTime = false;
    totalTime = 70;
    timeWhite = totalTime;
    timeBlack = totalTime;

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
    if (isCountDown) {
        if (isWhiteTurn) {
            timeWhite -= deltaTime.asSeconds();
            if (timeWhite <= 0) {
                timeWhite = 0;
                isCountDown = false;
                isOutOfTime = true;
                return "outoftime";
            }
        }
        else {
            timeBlack -= deltaTime.asSeconds();
            if (timeBlack <= 0) {
                timeBlack = 0;
                isCountDown = false;
                isOutOfTime = true;
                return "outoftime";
            }
        }
    }
    return "";
}

void TimeButton::updateRender() {
    auto ProcessStr = [&](Button* buttonSide, double time) -> void {
        std::string str = std::to_string((int)time / 60) + ":" + ((int)time % 60 < 10 ? "0" : "") + std::to_string((int)time % 60);
        if (time < 60) {
            str += "." + std::to_string((int)(time * 10) % 10);
        }
        buttonSide->setText(str);
    };
    ProcessStr(buttonWhite, timeWhite);
    ProcessStr(buttonBlack, timeBlack);
    buttonWhite->updateRender();
    buttonBlack->updateRender();
}

void TimeButton::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(*buttonWhite);
    target.draw(*buttonBlack);
}

void TimeButton::setColorBM(const ColorButMulti &colorButMulti) {
    buttonWhite->setColorBM(colorButMulti);
    buttonBlack->setColorBM(colorButMulti);
}

void TimeButton::setTime(int time)
{
    totalTime = time;
    timeWhite = totalTime;
    timeBlack = totalTime;
}

void TimeButton::setTurn(bool isWhiteturn) {
    this->isWhiteTurn = isWhiteturn;
}

void TimeButton::setIsCountDown(bool isCountDown) {
    this->isCountDown = isCountDown;
}

void TimeButton::changeTurn() {
    isWhiteTurn ^= 1;
    isCountDown = true;
}

void TimeButton::reset() {
    isWhiteTurn = true;
    isCountDown = false;
    isOutOfTime = false;
    timeWhite = totalTime;
    timeBlack = totalTime;
}