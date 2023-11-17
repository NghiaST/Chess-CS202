#include "TextBox.hpp"

///------------------------------------------------------------
///--------------------------TextBox---------------------------

TextBox::TextBox(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, 
            const sf::Font* sfFont, const ColorButton& colorButton, unsigned int sizeText, 
            std::string text, float thickness, Point renderOffsetText)
  : Graphic(renderPosition - renderSize / 2 * isPositionCenter, renderSize, true, 100)
{
    this->buttonID = buttonID;
    this->sfFont = sfFont;
    this->colorButton = colorButton;

    this->sizeText = sizeText;
    this->text = text;
    
    this->renderOffsetText = renderOffsetText;
    this->isRenderTextOrigin = isRenderTextOrigin;
    this->thickness = thickness;
    updateStaticRender();
}

TextBox::~TextBox() {
}

void TextBox::setRenderPosition(Point renderPosition) {
    Graphic::setRenderPosition(renderPosition);
    updateStaticRender();
}
void TextBox::setRenderSize(Point renderSize) {
    Graphic::setRenderSize(renderSize);
    updateStaticRender();
}
void TextBox::setFont(const sf::Font* sfFont) {
    this->sfFont = sfFont;
    sfText.setFont(*sfFont);
}
void TextBox::setSizeText(unsigned int sizeText) {
    this->sizeText = sizeText;
    sfText.setCharacterSize(sizeText);
    Point textPosition = renderPosition + isRenderTextOrigin * (renderSize / 2 - Point(sfText.getGlobalBounds().width, sizeText * 1.27) / 2) + renderOffsetText;
    sfText.setPosition(textPosition.to2f());
}
void TextBox::setText(std::string text) {
    this->text = text;
    updateStaticRender();
}
void TextBox::setRenderOffsetText(Point renderOffsetText) {
    this->renderOffsetText = renderOffsetText;
    updateStaticRender();
}
void TextBox::setIsRenderTextOrigin(bool isRenderTextOrigin) {
    this->isRenderTextOrigin = isRenderTextOrigin;
    updateStaticRender();
}
void TextBox::setThickness(float thickness) {
    this->thickness = thickness;
    shape.setOutlineThickness(thickness);
}
void TextBox::setColorButton(const ColorButton& colorButton) {
    this->colorButton = colorButton;
    updateStaticRender();
}
void TextBox::setButtonID(int buttonID) {
    this->buttonID = buttonID;
}

const sf::Font *TextBox::getFont() const {
    return sfFont;
}
int TextBox::getSizeText() const {
    return sizeText;
}
std::string TextBox::getText() const {
    return text;
}
Point TextBox::getRenderOffsetText() const {
    return renderOffsetText;
}
float TextBox::getThickness() const
{
    return thickness;
}
const ColorButton& TextBox::getColorButton() const {
    return colorButton;
}
int TextBox::getButtonID() const {
    return buttonID;
}

void TextBox::updateStaticRender() {
    shape.setPosition(renderPosition.to2f());
    shape.setSize(renderSize.to2f());
    shape.setFillColor(colorButton.FillColor);
    shape.setOutlineColor(colorButton.OutlineColor);
    shape.setOutlineThickness(thickness);

    sfText.setFont(*sfFont);
    sfText.setString(text);
    sfText.setCharacterSize(sizeText);
    
    Point textPosition = renderPosition + isRenderTextOrigin * (renderSize / 2 - Point(sfText.getGlobalBounds().width, sizeText * 1.27) / 2) + renderOffsetText;
    sfText.setPosition(textPosition.to2f());
    sfText.setFillColor(colorButton.TextColor);
    sfText.setOutlineColor(colorButton.TextColor);
}

void TextBox::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    if (!isPrint) return;
    target.draw(shape, states);
    target.draw(sfText, states);
}

///------------------------------------------------------------
///----------------------DynamicTextBox------------------------

DynamicTextBox::DynamicTextBox(int buttonID, Point renderPosition, Point renderSize, bool isPositionCenter, bool isRenderTextOrigin, const sf::Font *sfFont, const ColorButMulti &colorButMulti, unsigned int sizeText, std::string text, float thickness, Point renderOffsetText) 
    : TextBox(buttonID, renderPosition, renderSize, isPositionCenter, isRenderTextOrigin, sfFont, Color::ButtonDefault, sizeText, text, thickness, renderOffsetText)
{
    this->colorButMulti = colorButMulti;
    this->colorState = 0;
    changeColorState();
    timer = 0;

    velocity = 20;
    limit = 5;
    timeMove = 0;
    setRenderOffsetText(Point(0, 400));
}

DynamicTextBox::~DynamicTextBox() {
}

void DynamicTextBox::changeColorState() {
    colorState = (colorState + 1) % colorButMulti.getSize();
    setColorButton(colorButMulti.get(colorState));
    updateStaticRender();
}

void DynamicTextBox::update(sf::Time deltaTime) {
    timeMove += abs(velocity) * deltaTime.asSeconds();
    while (timeMove > 0.1) {
        timeMove -= 0.1;
        Point tmp = getRenderOffsetText();
        tmp.y += velocity / abs(velocity);
        if (tmp.y > limit) velocity = -abs(velocity);
        else if (tmp.y < -limit) velocity = abs(velocity);
        else velocity /= abs(velocity);
        setRenderOffsetText(tmp);
        updateStaticRender();
    }
    timer += deltaTime.asSeconds();
    if (timer > 1) {
        timer -= 1;
        changeColorState();
    }
}

int DynamicTextBox::getButtonState() const {
    return colorState;
}
