#include <IngameScreen/NotificationEndGame.hpp>
#include <DataControl/Theme.hpp>

NotificationEndGame::NotificationEndGame(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
            const sf::Font* sfFont, int result, std::string EndGameFlag)
  : Graphic(renderPosition - renderSize / 2 * isPositionCenter, renderSize, true, 100)
{
    Point middle = this->renderPosition + this->renderSize / 2;
    Point showButtonSize = this->renderSize;
    Point showButtonPosition = middle;
    std::string showButtonText = (result == 1 ? "White Win" : result == 0 ? "Black Win" : "Draw");

    Point offsetShowButton = Point(0, this->renderSize.y * -0.15);
    Point offsetText = Point(0, this->renderSize.y * 0.1);

    Point newGameButtonSize = Point(70, 30);
    Point backButtonSize = Point(70, 30);
    Point closeButtonSize = Point(15, 15);

    Point newGameButtonPosition = middle + Point(renderSize.x * -0.25, renderSize.y * 0.3);
    Point backButtonPosition = middle + Point(renderSize.x * +0.25, renderSize.y * 0.3);
    Point closeButtonPosition = this->renderPosition + Point(renderSize.x, 0) + Point(-10, 10);

    Theme* theme = Theme::getInstance();
    const ColorButMulti colorButMulti = theme->getColorDefault();

    showButton = new TextBox(buttonID + 1, showButtonPosition, showButtonSize, isPositionCenter, isRenderTextOrigin, sfFont, Color::ButtonLightCyan, 25, showButtonText, -1, offsetShowButton);
    text       = new TextBox(buttonID + 2, showButtonPosition, showButtonSize, isPositionCenter, isRenderTextOrigin, sfFont, Color::ButtonTextBlack, 10, EndGameFlag, -1, offsetText);

    newGameButton = new Button(buttonID + 3, newGameButtonPosition, newGameButtonSize, true, true, sfFont, colorButMulti, 12, "New Game", -1, Point(0, 0));
    backButton    = new Button(buttonID + 4, backButtonPosition, backButtonSize, true, true, sfFont, colorButMulti, 12, "Back", -1, Point(0, 0));
    closeButton   = new Button(buttonID + 5, closeButtonPosition, closeButtonSize, true, true, sfFont, colorButMulti, 12, "x", -1, Point(0, 0));
}

NotificationEndGame::~NotificationEndGame() {
    delete showButton;
    delete text;
    delete newGameButton;
    delete backButton;
    delete closeButton;
}

bool NotificationEndGame::handleEvent(const sf::Event &event) {
    if (!isPrint) return false;
    if (newGameButton->handleEvent(event)) {
        onclick = NEW_GAME;
        newGameButton->setButtonState(BTN_IDLE);
        setIsPrint(false);
        return true;
    }
    else if (backButton->handleEvent(event)) {
        onclick = BACK;
        backButton->setButtonState(BTN_IDLE);
        setIsPrint(false);
        return true;
    }
    else if (closeButton->handleEvent(event)) {
        onclick = CLOSE;
        closeButton->setButtonState(BTN_IDLE);
        setIsPrint(false);
        return true;
    }
    return false;
}

void NotificationEndGame::update(sf::Time deltaTime) {
    // do nothing
}

NotificationEndGame::Onclick NotificationEndGame::getOnclick() const {
    return onclick;
}

void NotificationEndGame::setEndGame(int result, std::string EndGameFlag) {
    std::string showButtonText = (result == 1 ? "White Win" : result == 0 ? "Black Win" : "Draw");
    showButton->setText(showButtonText);
    text->setText(EndGameFlag);
    Graphic::setIsPrint(true);
}

void NotificationEndGame::setEndGame(std::string showButtonText, std::string EndGameFlag) {
    showButton->setText(showButtonText);
    text->setText(EndGameFlag);
    Graphic::setIsPrint(true);
}

void NotificationEndGame::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!isPrint) return;
    target.draw(*showButton, states);
    target.draw(*text, states);
    target.draw(*newGameButton, states);
    target.draw(*backButton, states);
    target.draw(*closeButton, states);
}