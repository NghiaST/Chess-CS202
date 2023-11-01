#include "StaticButton.hpp"

StaticButton::StaticButton(int buttonID, Point renderPosition, Point renderSize, const sf::Font* sfFont,
            const ColorButton& colorButton, unsigned int sizeText, std::string text, 
            float thickness, bool isRenderTextOrigin, Point renderOffsetText)
  : Graphic(renderPosition, renderSize, true, 100)
{
    setButtonID(buttonID);
    setFont(sfFont);
    setColorButton(colorButton);

    setSizeText(sizeText);
    setText(text);

    setThickness(thickness);
    setIsRenderTextOrigin(isRenderTextOrigin);
    setRenderOffsetText(renderOffsetText);

    updateRender();
}

StaticButton::~StaticButton() {
}

void StaticButton::setFont(const sf::Font* sfFont) {
    this->sfFont = sfFont;
}
void StaticButton::setSizeText(unsigned int sizeText) {
    this->sizeText = sizeText;
}
void StaticButton::setText(std::string text) {
    this->text = text;
}
void StaticButton::setRenderOffsetText(Point renderOffsetText) {
    this->renderOffsetText = renderOffsetText;
}
void StaticButton::setIsRenderTextOrigin(bool isRenderTextOrigin) {
    this->isRenderTextOrigin = isRenderTextOrigin;
}
void StaticButton::setThickness(float thickness) {
    this->thickness = thickness;
}
void StaticButton::setColorButton(const ColorButton& colorButton) {
    this->colorButton = colorButton;
}
void StaticButton::setButtonID(int buttonID) {
    this->buttonID = buttonID;
}

const sf::Font *StaticButton::getFont() const {
    return sfFont;
}
int StaticButton::getSizeText() const {
    return sizeText;
}
std::string StaticButton::getText() const {
    return text;
}
float StaticButton::getThickness() const {
    return thickness;
}
const ColorButton& StaticButton::getColorButton() const {
    return colorButton;
}
int StaticButton::getButtonID() const {
    return buttonID;
}

void StaticButton::updateRender() {
    shape.setPosition(renderPosition.to2f());
    shape.setSize(renderSize.to2f());
    shape.setOutlineThickness(thickness);
    shape.setFillColor(colorButton.FillColor);
    shape.setOutlineColor(colorButton.OutlineColor);

    sizeText = 30;
    Point textPosition = renderPosition + isRenderTextOrigin * (renderSize / 2 - Point(sfText.getGlobalBounds().width, sizeText * 1.27) / 2) + renderOffsetText;
    sfText.setFont(*sfFont);
    sfText.setString(text);
    sfText.setFillColor(sf::Color::White);
    sfText.setCharacterSize(sizeText);
    sfText.setPosition(textPosition.to2f());
    sfText.setOutlineColor(colorButton.TextColor);
}

void StaticButton::draw(sf::RenderTarget &target, sf::RenderStates state) const {
    if (!isPrint) return;
    target.draw(shape);
    target.draw(sfText);
}

void StaticButton::render(sf::RenderTarget &target, sf::RenderStates state) const {
    if (!isPrint) return;
    target.draw(shape);
    target.draw(sfText);
}