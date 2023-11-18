#include <DataControl/ButtonOption.hpp>

ButtonOption::ButtonOption(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, const sf::Font *sfFont, const ColorButMulti &colorButMulti, unsigned int sizeText, std::vector<std::string> textOptions, int currentSelection, float thickness, Point renderOffsetText) 
    : Graphic(renderPosition - renderSize / 2 * isPositionCenter, renderSize, true, 100)
{
    Point rollSize = Point(renderSize.y * 0.7, renderSize.y);
    Point mainSize = Point(renderSize.x - rollSize.x * 2, renderSize.y);
    Point renderPositionLeft = this->renderPosition;
    Point renderPositionMain = this->renderPosition + Point(rollSize.x, 0);
    Point renderPositionRight = this->renderPosition + Point(rollSize.x + mainSize.x, 0);

    mainButton = new Button(buttonID + 1, renderPositionMain, mainSize, false, isRenderTextOrigin, sfFont, colorButMulti, sizeText, "", thickness);
    rollLeft = new Button(buttonID + 2, renderPositionLeft, rollSize, false, isRenderTextOrigin, sfFont, colorButMulti, sizeText, "<", thickness);
    rollRight = new Button(buttonID + 3, renderPositionRight, rollSize, false, isRenderTextOrigin, sfFont, colorButMulti, sizeText, ">", thickness);

    this->textOptions = textOptions;
    setCurrentSelection(currentSelection);
}

ButtonOption::~ButtonOption() {
    delete mainButton;
    delete rollLeft;
    delete rollRight;
}

bool ButtonOption::handleEvent(const sf::Event &event) {
    mainButton->handleEvent(event);
    bool isRollLeft = rollLeft->handleEvent(event);
    bool isRollRight = rollRight->handleEvent(event);

    if (isRollLeft) {
        setCurrentSelection(currentSelection - 1);
        return true;
    }
    else if (isRollRight) {
        setCurrentSelection(currentSelection + 1);
        return true;
    }
    return false;
}

void ButtonOption::update(sf::Time deltaTime) {
    // do nothing
}

// void ButtonOption::updateRender() {
//     // mainButton->updateRender();
//     // rollLeft->updateRender();
//     // rollRight->updateRender();
// }

void ButtonOption::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(*mainButton, states);
    target.draw(*rollLeft, states);
    target.draw(*rollRight, states);
}

void ButtonOption::setColorBM(const ColorButMulti &colorButMulti) {
    mainButton->setColorBM(colorButMulti);
    rollLeft->setColorBM(colorButMulti);
    rollRight->setColorBM(colorButMulti);
}

void ButtonOption::setCurrentSelection(int currentSelection)
{
    this->currentSelection = currentSelection;
    if (this->currentSelection < 0) {
        this->currentSelection = (int) textOptions.size() - 1;
    }
    else if (this->currentSelection >= (int) textOptions.size()) {
        this->currentSelection = 0;
    }
    mainButton->setText(textOptions[this->currentSelection]);
}

int ButtonOption::getCurrentSelection() const {
    return currentSelection;
}